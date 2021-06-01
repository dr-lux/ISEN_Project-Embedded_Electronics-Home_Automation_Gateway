<!DOCTYPE html>
<html>

<head>
    <title>
        Home Automation Gateway | Pipes
    </title>
</head>

<body style="text-align:center;">

<?php

if(isset($_POST['red_on'])) {
    shell_exec("/root/project A 1 1 9");
}

if(isset($_POST['red_off'])) {
    shell_exec("/root/project A 1 0 9");
}

if(isset($_POST['green_on'])) {
    shell_exec("/root/project B 1 1 9");
}

if(isset($_POST['green_off'])) {
    shell_exec("/root/project B 1 0 9");
}

if(isset($_POST['blue_on'])) {
    shell_exec("/root/project C 1 1 9");
}

if(isset($_POST['blue_off'])) {
    shell_exec("/root/project C 1 0 9");
}

?>

<form method="post">
    <input type="submit" name="red_on"
           value="RED ON"/>

    <input type="submit" name="red_off"
           value="RED OFF"/>

    <input type="submit" name="green_on"
           value="GREEN ON"/>

    <input type="submit" name="green_off"
           value="GREEN OFF"/>

    <input type="submit" name="blue_on"
           value="BLUE ON"/>

    <input type="submit" name="blue_off"
           value="BLUE OFF"/>

    <input type="submit" name="all_on"
           value="ALL ON"/>

    <input type="submit" name="all_off"
           value="all OFF"/>
</form>
</head>

</html>
