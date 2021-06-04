setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();
    var xhttp1 = new XMLHttpRequest();

    var xhttp2 = new XMLHttpRequest();
    var xhttp3 = new XMLHttpRequest();
    var xhttp4 = new XMLHttpRequest();

    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("luminosite").innerHTML = this.responseText;
        }
    };

    xhttp.open("GET", "lireLuminosite", true);
    xhttp.send();

    xhttp1.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("temperature").innerHTML = this.responseText;
        }
    };

    xhttp1.open("GET", "lireTemperature", true);
    xhttp1.send();

    xhttp2.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("tension").innerHTML = this.responseText;
        }
    };

    xhttp2.open("GET", "lireTension", true);
    xhttp2.send();

    xhttp3.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("courant").innerHTML = this.responseText;
        }
    };

    xhttp3.open("GET", "lireCourant", true);
    xhttp3.send();

    xhttp4.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("puissance").innerHTML = this.responseText;
        }
    };

    xhttp4.open("GET", "lirePuissance", true);
    xhttp4.send();
}, 2000)