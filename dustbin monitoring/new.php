<?php
// Initialize the session
session_start();
 
// Check if the user is logged in, if not then redirect him to login page
if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
    header("location: index.php");
    exit;
}
?>

<!DOCTYPE html>
<html>
<head>
<title>Dust Bin System</title>
<link rel = "icon" href = 
"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" 
        type = "image/x-icon">
<meta name="viewport" content="width=device-width, initial-scale=1">
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
</style>
</head>
<body>

<div class="topnav">
  <a href="data.php">Dust Bin Monitoring</a>
  <a href="logout.php">Logout</a>
</div>
<h1><center>Dust Bin Monitoring System</center></h1>

<center><img src="https://lh3.googleusercontent.com/proxy/PzGtHvSNwddiugbMeCyMq0xNEc8D7MjFkR13pDbaSRgkpRR2lAhLKhsbicf4bIqzAqdmS7DlSk5W-_F5Jcut6XxO4JTPIPqPHk9Z1orwHFFpDSdsqIZEYfBnJER-BYdS8S447_oFXBs"></center>

</body>
</html>