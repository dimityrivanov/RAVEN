<?php
shell_exec('sh startCamera.sh');
?>
<head>
    <link rel="stylesheet" href="style.css"/>
<link rel="stylesheet" href="fancybox/source/jquery.fancybox.css?v=2.1.5" type="text/css" media="screen" />
    <script src="//code.jquery.com/jquery-1.11.0.min.js"></script>
    <script src="http://d3lp1msu2r81bx.cloudfront.net/kjs/js/lib/kinetic-v5.0.2.min.js"></script>
<script type="text/javascript" src="fancybox/source/jquery.fancybox.pack.js?v=2.1.5"></script>
</head>
<body>
<div id="header">
	<div id="logos"></div>
</div>
<div id="map"></div>
<div id="sizeMetres">
	<div id="sizeMetresLabel">Length of map side:&nbsp;</div>
	<div id="sizeMetresValue"></div>
</div>
<iframe id="videoFrame" width="650" height="500" src="http://192.168.1.109:9000/javascript_simple.html"></iframe>
<div id="cameraRotate">
	<div id="cameraRotateLabel1">Y angle</div>
	<div id="cameraRotateValue1" contenteditable="true">0</div>
	<div id="cameraRotateLabel2">X angle</div>
	<div id="cameraRotateValue2" contenteditable="true">90</div>
	<div id="cameraRotateSubmit">Rotate Camera</div>
</div>


<script>
$(function(){
	updateSizeMetres();
	$('#cameraRotateValue1').blur(function(){
		yVal = parseInt($(this).html());
		if(yVal<0 || yVal>180)
		{
			yVal = 0;
		}
		$(this).html(yVal);
	});
	$('#cameraRotateValue2').blur(function(){
		xVal = parseInt($(this).html());
		if(xVal<0 || xVal>180)
		{
			xVal = 90;
		}
		$(this).html(xVal);
	});
	$('#cameraRotateSubmit').click(function(){
		var y = $('#cameraRotateValue1').html();
		var x = $('#cameraRotateValue2').html();
		var command = y+';'+x;
		$.ajax
	        ({
			type:"POST",
			async:false,
			url:"angle.php",
			data:{command:command}
	        }).done(function(msg)
        	{
		});
	});
});
    var sizePx = 600;
    window.sizeMetres = 1;
    window.thumbnailSize = 20;
    window.prevX = sizePx/2;
    window.prevY = sizePx/2;
    window.points = [window.prevX,window.prevY];
    window.prevAngle = Math.PI/2;

    var stage = new Kinetic.Stage({
        container: 'map',
        width: sizePx,
        height: sizePx
    });
    var layer = new Kinetic.Layer();
    var path = new Kinetic.Line({
        points:window.points,
        stroke:'#FF5000',
        strokeWidth:2,
        lineJoin:'round',
        dash:[10,3],
        id:'path'
    });
    layer.add(path);
    stage.add(layer);
    
    
    setInterval(function(){
        $.ajax
        ({
            type:"POST",
            async:false,
            url:"getBuffer.php"
        }).done(function(msg)
        {
		//console.log(msg);
            var lines = msg.replace("\r\n","").split(';'); //remove \r\n from end of line
            if(lines.length === 0)return;
            $.each(lines, function(index, line){
                if(typeof(line) !== "undefined" && line.length > 0)
                {
                    //$('body').append('line: '+line);
                    var lineParts = line.split(':');
                    var label = lineParts[0];
			if(label == 'l')
			{
				var values = lineParts[1].split(',');
				var distance = mToPx(parseFloat(values[0])/100);
				var heading = parseFloat(values[1]);
				//$('body').append('<br/>d: '+distance+'; heading: '+heading);
				
				var newAngle = Math.PI/2 - heading;// + window.prevAngle;
				if(newAngle > 2*Math.PI)
				{
					newAngle -= 2*Math.PI;
				}
				var newX = prevX + Math.cos(newAngle)*distance;
				var newY = prevY - Math.sin(newAngle)*distance;
				
				window.points.push(newX);
				window.points.push(newY);
				window.prevX = newX;
				window.prevY = newY;
				window.prevAngle = newAngle;
				
				if(newX<0 || newX>window.sizePx || newY<0 || newY>window.sizePx)
				{
					for(var i in window.points)
					{
					    window.points[i] = (window.sizePx + window.points[i].valueOf())/3;
					}
					window.prevX = (window.prevX.valueOf() + window.sizePx)/3;
					window.prevY = (window.prevY.valueOf() + window.sizePx)/3;
					window.sizeMetres = window.sizeMetres.valueOf()*3;
					window.thumbnailSize = parseInt(window.thumbnailSize.valueOf()/2);
					$.each(stage.get('Rect'), function(rectIndex, rect){
						rect.setX((window.sizePx + rect.getX())/3);
						rect.setY((window.sizePx + rect.getY())/3);
						rect.setWidth(window.thumbnailSize);
						rect.setHeight(window.thumbnailSize);
					})					

					updateSizeMetres();
    				}	
			}
			else if(label == 'p')
			{
				//console.log(lineParts[1]);
				var lastX = parseInt(window.points[window.points.length - 2]);
				var lastY = parseInt(window.points[window.points.length - 1]);
				var picThumbnail = new Kinetic.Rect({
					x:parseInt(lastX - window.thumbnailSize/2),
					y:parseInt(lastY - window.thumbnailSize/2),
					width:window.thumbnailSize,
					height:window.thumbnailSize,
					fill:'#02AEEE',
					stroke:'#02AEEE',
					strokeWidth:0,
					id:lineParts[1]
				});
				picThumbnail.on('click',function(evt){
					invokeFancybox(evt.target.getId());
				});
				layer.add(picThumbnail);
			}
                }
            });
            path.setPoints(window.points);
            layer.draw();
        });
    },500);
    
    function mToPx(metres)
    {
        return metres*sizePx/sizeMetres;
    }

	function updateSizeMetres()
	{
		$('#sizeMetresValue').html(window.sizeMetres+" m");
	}
	
	function invokeFancybox(picName)
	{
//		console.log('ads'+picName);
		$.fancybox.open('images/'+picName+'.jpg', {});
	}
	
</script>
</body>