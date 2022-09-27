<html>
<head>
    <title>Dust Bin Monitoring System</title>
        <link rel = "icon" href = 
"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" 
        type = "image/x-icon">
<style>
body {
  margin: 0;
  font-family: Arial, Helvetica, sans-serif;
}

.topnav {
  overflow: hidden;
  background-color: #333;
}

.topnav a {
  float: left;
  color: #f2f2f2;
  text-align: center;
  padding: 14px 16px;
  text-decoration: none;
  font-size: 17px;
}

.topnav a:hover {
  background-color: #ddd;
  color: black;
}

.topnav a.active {
  background-color: #04AA6D;
  color: white;
}

table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  width: 100%;
}

td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}

tr:nth-child(even) {
  background-color: #dddddd;
}
</style>
</head>

<body>

<div class="topnav">
  <a href="data.php">Dust Bin Monitoring</a>
  <a href="logout.php">Logout</a>
</div>

</body>
    <body>
        <h2>Dustbin Data</h2>
        <?php
        require_once "config.php";
            $i=0;
            
            $query = "SELECT timetaken from dustbin WHERE status='checkin'";
            $result1 = mysqli_query($conn,$query);
            $row=array();
            while($x = mysqli_fetch_assoc($result1))
                $row[] = $x;
            
            $query2 = "SELECT timetaken from dustbin WHERE status='checkout'";
            $result2 = mysqli_query($conn,$query2);
            $row2=array();
            while($x2 = mysqli_fetch_assoc($result2))
                $row2[] = $x2;
            
            $query3 = "SELECT users.username,dustbin.cardid,dustbin.timetaken, dustbin.date_now, dustbin.binlevel FROM dustbin INNER JOIN users ON dustbin.cardid=users.cardid GROUP BY dustbin.cardid ORDER BY dustbin.date_now";
            $result3 = mysqli_query($conn,$query3);
            
            $row4=array();

                echo "<table>"; 
                echo "<tr><td>" ."Username". "</td><td> " ."Card Id"."</td><td>" ."Time In". "</td><td>" ."Time Out"."</td><td>"."Time Taken"."</td><td>"."Date". "</td><td> " ."Bin Level"."</td></tr>"; 
            
               if ($result3 = $conn->query($query3)) {
                    while($row3 = mysqli_fetch_array($result3))
                    {  $row4[] = $row3;
                        while($i<count($row4)){
                        echo "<tr><td>" . $row3['username'] . "</td><td> " . $row3['cardid'] ."</td><td>" . implode("",$row[$i]). "</td><td>" . implode("",$row2[$i])."</td><td>" . $row3['timetaken']."</td><td>" . $row3['date_now']."</td><td>" .$row3['binlevel'] ."</td></tr>"; 
                        $i++;
                        }
                    }
                echo "</table>"; //Close the table in HTML
                $result3->free();
                }else{
                    echo("Error description: " . $mysqli -> error);
                } 
                    
           
        ?>
    </body>
</html>