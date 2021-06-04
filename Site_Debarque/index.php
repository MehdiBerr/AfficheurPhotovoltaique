<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <meta name="viewport" content="device-width, initial-scale=1.0">
    <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>
    <script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>
    <link href='https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/solar/bootstrap.min.css' rel='stylesheet'>
    <title>Accueil PRT7</title>
    <meta name='description' content='Interface Web ESP32 pour afficher des mesures sur un panneau photovoltaïque'>
    <meta name='author' content='Binome9_4GE2_2020/2021_INSALyon'>

    <link href='css/bootstrap.min.css' rel='stylesheet'>
    <link href='css/style.css' rel='stylesheet'>
    <link rel="stylesheet" href="style.css">
  </head>
  <body>
  <div id="menu">
  <ul id="onglets" class='nav nav-pills'>
    <li class="active"><a href="index.php"> Accueil </a></li>
    <li><a href="EssaiTab.php"> Données </a></li>
    <li><a href="PagePRT7.php"> Ajouter un Donnée </a></li>
    <li><a href="Equipe.php"> L'équipe </a></li>
  </ul>
</div>
<div class='container-fluid'>
	<div class='row'>
		<div class='col-md-12'>
			<h1>
				PRT7 Maquette WebServer
			</h1>
			<h3>
				Mesures panneau photovoltaïque<br><br>
			</h3>
			<ul class='nav nav-pills'>
				<li class='nav-item'>
					 <a class='nav-link btn btn-primary' href='#'>Température <span class='badge badge-light'>42</span> °C</a>
				</li>
        <li class='nav-item'>
           <a class='nav-link btn btn-primary' href='#'>Luminosité <span class='badge badge-light'>16</span> lux</a>
        </li>
				<li class='nav-item'>
					 <a class='nav-link' href='#'>Luminosité <span class='badge badge-secondary'>16</span> lux</a>
				</li>
			</ul>
			<table class='table table-striped table-hover'>
				<thead>
					<tr>
						<th>
							Mesure
						</th>
						<th>
							Unité
						</th>
						<th>
							Description
						</th>
						<th>
							Valeur
						</th>
					</tr>
				</thead>
				<tbody>
					<tr>
						<td>
							Vs
						</td>
						<td>
							Volt
						</td>
						<td>
							Tension de sortie MPPT
						</td>
						<td>
							0
						</td>
					</tr>
					<tr>
						<td>
							Is
						</td>
						<td>
							Ampère
						</td>
						<td>
							Courant de sortie MPPT
						</td>
						<td>
							0
						</td>
					</tr>
					<tr>
						<td>
							P
						</td>
						<td>
							Watt
						</td>
						<td>
							Puissance de sortie MPPT
						</td>
						<td>
							0
						</td>
					</tr>
				</tbody>
			</table>
		</div>
	</div>
</div>

    <script src='js/jquery.min.js'></script>
    <script src='js/bootstrap.min.js'></script>
    <script src='js/scripts.js'></script>
  </body>
</html>
