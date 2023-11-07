<?php
include_once 'koneksi.php';
$kon = new koneksi();

    // $data = $_GET['sensor'];
    // echo $data;

    // $result = $kon->kueri("SELECT * FROM kwh");
    // $data = $kon->hasil_data($result);
    // var_dump($data);
    if(isset($_GET['sensor'] )){
        $sensor = $_GET['sensor'];
        $update = $kon->kueri("UPDATE `kwh` SET `pzeem`='$sensor' WHERE id = 1 ");
    }