<?php
class Koneksi
{
    private $konek;
    private $host = "localhost";
    private $user = "root";
    private $pass = "";
    private $db = "monitorkonsumsienergi";

    private function sambung()
    {
        try {
            $this->konek = new PDO("mysql:host=" . $this->host . ";dbname=" . $this->db . ";charset=utf8mb4", $this->user, $this->pass);
            $this->konek->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            $this->konek->setAttribute(PDO::ATTR_EMULATE_PREPARES, true);
            return $this->konek;
        } catch (PDOException $ex) {
            return NULL;
        }
    }
    public function kueri($sql)
    {
        $this->sambung();
        $hasil = $this->konek->prepare($sql);
        $hasil->execute();
        return $hasil;
    }

    public function hasil_data($arg)
    {
        return $arg->fetch(PDO::FETCH_ASSOC);
    }
    public function hasil_array($arg)
    {
        return $arg->fetchAll(PDO::FETCH_ASSOC);
    }


    public function jumlah_data($arg)
    {
        return $arg->rowCount();
    }
}
