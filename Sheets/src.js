
function randomChoice(arr)
{
    return arr[Math.floor(arr.length * Math.random())];
}

color = randomChoice(["#1abc9c", "#2ecc71", "#2c3e50", "#f39c12"]);
function Circle(x, y,color)
{
    const svgns = "http://www.w3.org/2000/svg";
    var container = document.getElementById('B');

    var circle = document.createElementNS(svgns, 'circle');
    circle.setAttributeNS(null, 'cx', x);
    circle.setAttributeNS(null, 'cy', y);
    circle.setAttributeNS(null, 'r', 4);
    circle.setAttributeNS(null, 'style', 'fill: ' + color + '; stroke: blue; stroke-width: 1px;');
    container.appendChild(circle);
}

$(document).mousemove(function (event)
{
    x = event.pageX - $('#B').offset().left;
    y = event.pageY - $('#B').offset().top;
    $("#span").text(x + " , " + y);
}
);

var blue = 1;

$(window).keypress(function (e)
{
    if (e.key === ' ' || e.key === 'Spacebar')
    {
        e.preventDefault()
        console.log('Space pressed')
        blue = 1 - blue;
        if (blue)
            $("#Blue").attr("fill", "blue");
        else
            $("#Blue").attr("fill", "red");
    }
}
)

var blues = [], reds = [];

$('#B').click(function (e)
{
    var posX = $(this).offset().left,
    posY = $(this).offset().top;
    x = e.pageX - posX;
    y = (e.pageY - posY);
    if (blue == 1)
    {
        blues.push([x, y]);
        Circle(x, y ,"blue");
    }
    else
    {
        reds.push([x, y]);
        Circle(x, y ,"red");
    }
}
);

function coperS(S) {
  const el = document.createElement('textarea');
  el.value = S;
  document.body.appendChild(el);
  el.select();
  document.execCommand('copy');
  document.body.removeChild(el);
}

function coperRed()
{
    var s=JSON.stringify(reds);
    s = s.split("[").join("{");
    s = s.split("]").join("}");
    coperS(s);
}

function coperBlue()
{
    var s=JSON.stringify(blues);
    s = s.split("[").join("{");
    s = s.split("]").join("}");
    coperS(s);
}