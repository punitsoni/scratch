var pg;
var canvas;
var rotX, rotY;

rotX = 0.0;
rotY = 0.0;

UPDATE_FREQ = 30;
ROT_DPS = 30;

function setup() {
    w = $('#sketch').width();
    h = $('#sketch').height();
    h = w * 9.0/16.0;
    canvas = createCanvas(w, h, WEBGL);
    canvas.parent('sketch');
    setInterval(onTimer, 1000*(1/UPDATE_FREQ));
}

function onTimer() {
    rotX = PI/6;
    var d = ROT_DPS * (1 / UPDATE_FREQ);
    rotY = rotY + radians(d);
}

function myline(x1, y1, z1, x2, y2, z2) {
    beginShape();
    vertex(x1, y1, z1);
    vertex(x2, y2, z2);
    endShape();
}

function draw(){
    background(240, 240, 230);

    normalMaterial();

    stroke(220, 20, 20);
    myline(0, 0, 0, 100, 0, 0);
    // stroke(20, 220, 20);
    // myline(0, -100, 0, 0, 1000, 0);
    // stroke(20, 20, 220);
    // myline(0, 0, -100, 0, 0, 1000);

    //stroke(0);

    /* draw the cube */
    push();
    // rotateX(rotX);
    // rotateX(PI/4);
    // rotateY(rotY);
    // rotateZ(PI/4);
    box(200, 200, 200);
    pop();

    /* dashboard text */
    var text = "";
    text += "mouse_position = " + mouseX + ", " + floor(mouseY) + '\n';
    text += "frame_rate = " + floor(frameRate()); + '\n'


    $('#dash').html('<pre>' + text + '</pre>');
}
