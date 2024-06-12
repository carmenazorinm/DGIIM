<h2>Listado alumnos</h2>
<?php
$mysql = new mysqli('db', 'admin', 'ise2023','ise2023'); 
if ($mysql->connect_error) {
 die('No pudo conectarse: ' . $mysql->connected_error); echo '<h1>Conectado satisfactoriamente</h1>';
}
?>
<h1>Contenido de la tabla Alumnos</h1>
<table border="1"> <tr><td>Id</td><td>Nombre</td><td>Email</td></tr>
<?php
$sql = "SELECT id, dni, nombre, apellidos, email from alumnos"; $result = $mysql->query($sql);
if ($result->num_rows > 0) {
	while($row = $result->fetch_assoc()) {
		echo "<tr><td>".$row["id"]."</td><td>".$row["nombre"]." ". $row["apellidos"]."</td>";
		echo "<td>".$row["email"]."</td></tr>\n"; 
	}
}
$mysql->close();
?>
