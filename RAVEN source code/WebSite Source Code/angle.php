<?php
if(isset($_POST['command']) && $_POST['command']!='')
{
	$command = $_POST['command'];
}
$commandParts = explode(';',$command);
if($commandParts[0]>0 && $commandParts[0]<180 && $commandParts[1]>0 && $commandParts[1]<180)
{
	file_put_contents('camera.txt', $command);
}
?>
