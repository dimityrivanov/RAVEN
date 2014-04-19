<?php
$buffer = file_get_contents('buffer.txt');
file_put_contents('buffer.txt', '');
echo $buffer;
?>
