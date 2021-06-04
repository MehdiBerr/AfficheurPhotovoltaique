<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Formulaire PRT7</title>
    <link rel="stylesheet" href="style.css">
  </head>
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
<h1>Formulaire de Données du PRT 7</h1>
<br/ >
<br/ >

    <form action="PagePRT7.php" method="post" name="formulaire">
      <p>
        <label for="x"></label>
        Valeur en x :
        <input id= "x" name="ValX" type= "text" placeholder="Entrez la valeur en x...">
      </p>
      <p>
      <label for="y"></label>
      <br/ >
        Valeur en y :
        <input id= "y" name="ValY" type= "text" placeholder="Entrez la valeur en y...">
      </p>
     <p>
     <br/ >
        <label for="sd"></label>
        <input id="sd" name="Envoyer" type= "submit" value="Envoyer">
        <label for="clr"></label>
        <input id="clr" name="Clear" type= "reset" value="Effacer">
      </p>
    </form>
  </body>
  <?php
        if(isset($_POST['ValX']))
        {
          $fichier = fopen('ValuesX.txt','r+');
          rewind($fichier);
          $vues =fgets($fichier)+0.0;
          $vues++;
          fseek($fichier,0);
          fputs($fichier, $vues);
          fseek($fichier,0, SEEK_END);
          fputs($fichier, "\r\n".$_POST['ValX']);
          fclose($fichier);
        }
        if(isset($_POST['ValY']))
        {
          $fichier = fopen('ValuesY.txt','r+');
          rewind($fichier);
          $vues =fgets($fichier)+0.0;
          $vues++;
          fseek($fichier,0);
          fputs($fichier, $vues);
          fseek($fichier,0, SEEK_END);
          fputs($fichier, "\r\n".$_POST['ValY']);
          fclose($fichier);
        }
    ?>
</html>