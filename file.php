<?php
/*
Configuration start
*/
$path = "youdontknowthis.php"; //The path to the file, in which the data will be saved.
/*
Configuration end
*/

function getData($key) {
    $data = file_get_contents($GLOBALS["path"]);
    $data = explode("?>", $data)[1];
    $lines = explode("\n", $data);
    foreach ($lines as &$value) {
        $ret = explode(";", $value);
        if (strcmp($ret[1], $key) == 0) {
            return $ret;
        }
        if (strcmp($ret[2], $key) == 0) {
            return $ret;
        }
    }
}
function isFree($key) {
    $data = file_get_contents($GLOBALS["path"]);
    $data = explode("?>", $data)[1];
    $lines = explode("\n", $data);
    foreach ($lines as &$value) {
        if (strpos($value,$key) !== false) {
            return false;
        }
    }
    return true;
}
function save($timestamp, $publickey, $privatekey, $filehash) {
    if(!file_exists($GLOBALS["path"])) {
        $myfile = fopen($GLOBALS["path"], "w") or die("Unable to open file!");
        fwrite($myfile, '<?php exit("");?>');
        fclose($myfile);
    }
    $myfile = fopen($GLOBALS["path"], "a") or die("Unable to open file!");
    fwrite($myfile, $timestamp.";".$publickey.";".$privatekey.";".$filehash."\n");
    fclose($myfile);
}
?>
