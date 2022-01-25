<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<body>
<?php

$hostname = "localhost";
$username = "pi";
$password = "elektromechanika";
$db = "systemdata";

$dbconnect=mysqli_connect($hostname,$username,$password,$db);

if ($dbconnect->connect_error) {
  die("Database connection failed: " . $dbconnect->connect_error);
}

?>

<table border="1" align="center">
<tr>
  <td>Fény</td>
  <td>Vízmélység</td>
  <td>Páratartalom</td>
  <td>Hőmérséklet</td>
  <td>Időbélyeg</td>
</tr>

<?php


$query = mysqli_query($dbconnect, "SELECT * FROM ontozorendszer order by Idobelyeg desc LIMIT 20")
   or die (mysqli_error($dbconnect));

while ($row = mysqli_fetch_array($query)) {
  echo
   "<tr>
    <td>{$row['feny']}</td>
    <td>{$row['vizmelyseg']}</td>
    <td>{$row['paratartalom']}</td>
    <td>{$row['homerseklet']}</td>
    <td>{$row['Idobelyeg']}</td>
   </tr>\n";
}

header("Refresh:10");
?>
</table>
</body>
</html>
