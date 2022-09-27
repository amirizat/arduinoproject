<?php

    require_once "config.php";

    date_default_timezone_set("Asia/Kuala_Lumpur");
    $error = '';
    $idcard = '';
    $binlevel = '';
    $date_now = date("d/m/Y") ;
    $time_now = date("h:i:sa");

    function clean_text($string)
    {
    $string = trim($string);
    $string = stripslashes($string);
    $string = htmlspecialchars($string);
    return $string;
    }

    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if(empty($_POST["idcard"])||empty($_POST["binlevel"])||empty($_POST["status"])){
            $error .= "Make sure idcard or dustbin or status level is inserted";
        }else{
            $idcard = clean_text($_POST["idcard"]);
            $binlevel = clean_text($_POST["binlevel"]);
            $status = clean_text($_POST["status"]);
         //if(!preg_match("/^[a-zA-Z ]*$/",$no_people))
         //{
          //$error .= '<p><label class="text-danger">Only letters and white space allowed</label></p>';
         //}
        }
        if($error == ''){

            $sql = "SELECT cardid FROM user WHERE cardid='$idcard'";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) {

                $sql2 = "INSERT INTO dustbin (cardid, status,timetaken, date_now, binlevel)
                VALUES ('".$idcard."', '".$status."','".$time_now."', '".$date_now."', '".$binlevel."')";

                if ($conn->query($sql2) === TRUE) {
                    echo "200";
                    $idcard = '';
                    $temp = '';
                    $date_now = '';
                    $time_now = '';
                    $binlevel = '';
                } else {
                    echo "error insert";
                }

            } else {
                echo "no matching card";
            }
        }else{
            echo $error;
        }
       }else{
           echo "404";
       }
	$conn->close();
?>