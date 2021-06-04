<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <meta name="viewport" content="device-width, initial-scale=1.0">
    <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>
    <script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>
    <link href='https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/solar/bootstrap.min.css' rel='stylesheet'>
    <title>Données PRT7</title>
    <meta name='description' content='Interface Web ESP32 pour afficher des mesures sur un panneau photovoltaïque'>
    <meta name='author' content='Binome9_4GE2_2020/2021_INSALyon'>

    <link href='css/bootstrap.min.css' rel='stylesheet'>
    <link href='css/style.css' rel='stylesheet'>
    <link rel="stylesheet" href="style.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>
    <link rel="stylesheet" href="style.css">
  </head>
  <?php

        //Réalisation du tableau $tab à partir d'un fichier texte
        //BEGIN
        $fichier = fopen('ValuesX.txt','r+');
        $i=0;
        $n=fgets($fichier);
        while($i<$n)
        {
            $tab[$i][0] = fgets($fichier);
            //echo $tab[$i][0]."<br/ >";
            $i++;
        }

        fclose($fichier2);
        $fichier2 = fopen('ValuesY.txt','r+');
        $i=0;
        $n=fgets($fichier2);
        while($i<$n)
        {
            $tab[$i][1] = fgets($fichier2);
            if($i>0)
            {
              $tab1[$i-1] = $tab[$i][1]+0.0;
              //echo $tab1[$i-1]."<br/ >";
            }
            
            $i++;
        }

        fclose($fichier);
        //END
        $Taillel =$n+0.0;
        $Taillec =2;
    ?>

  <body>
  <div id="menu">
  <ul id="onglets">
    <li class="active"><a href="index.php"> Accueil </a></li>
    <li><a href="EssaiTab.php"> Données </a></li>
    <li><a href="PagePRT7.php"> Ajouter un Donnée </a></li>
    <li><a href="Equipe.php"> L'équipe </a></li>
  </ul>
</div>
<br/ >
    <h1>Tableaux de données du PRT 7</h1>
    <table class="tableau-style">
      <thead>
        <tr>
        <?php
            for($i=0;$i<$Taillec;$i++)
            {
                echo "<th>".$tab[0][$i]."</th>";
            }
        ?>
        </tr>
      </thead>
      <tbody>
        <?php
            for($i=1;$i<$Taillel;$i++)
            {
                echo "<tr>";
                for($j=0;$j<$Taillec;$j++)
                {
                    echo "<td>";
                    echo $tab[$i][$j];
                    echo "</td>";
                }
                echo "</tr>";
            }
        ?>
      </tbody>
    </table>
    <canvas id="graph1"></canvas>
    <form action="EssaiTab.php" method="post" name="formulaire">
     <p>
        <br/ ><br/ ><br/ >
        <label for="sd"></label>
        <input id="sd" name="Refresh" type= "submit" value="Refresh">
      </p>
      <p>
      <br/ >
      <br/ >
      <br/ >
      <br/ >
      <br/ >
      Voici les premier résultats que nous imaginons...
      <br/ >
      <br/ >
      <br/ >
      </p>

    </form>
  </body>
</html>

<script>
  var ctx = document.getElementById('graph1').getContext('2d')
  var tab=[0];
  tab.pop();
  var Taillel = '<?php echo $Taillel; ?>';
  <?php echo "var tab1 = '".implode("<>", $tab1)."'.split('<>');"; ?>
  for(i=1;i<Taillel;i++)
  {
      tab.push(i);
  }


  var data = {
      labels: tab,
      datasets: [
          {
              backgroundColor: '#BB0B0B',
              data: tab1,
              label: 'Premier test',
          }
      ]
  }

  var options = {
      responsive: true,
      plugins: {
        title: {
          display: true,
          text: 'Chart Title',
        }
      },
  }

  var config = {
      type: 'line',
      data: data,
      options: options
  }
  var graph1 = new Chart(ctx, config)
</script>
