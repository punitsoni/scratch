var canvas = $("#renderCanvas").get(0);
var b = BABYLON;
var engine = new b.Engine(canvas, true);

function createAxes(size, scene) {
    var axisX = b.Mesh.CreateLines("axisX", [
        new b.Vector3.Zero(), new b.Vector3(size, 0, 0)
    ], scene);
    axisX.color = new b.Color3(1, 0, 0);
    var axisY = b.Mesh.CreateLines("axisY", [
        new b.Vector3.Zero(), new b.Vector3(0, size, 0)
    ], scene);
    axisY.color = new b.Color3(0, 1, 0);
    var axisZ = b.Mesh.CreateLines("axisZ", [
        new b.Vector3.Zero(), new b.Vector3(0, 0, size)
    ], scene);
    axisZ.color = new b.Color3(0, 0, 1);
};

function createCone(scene) {

    var cone = b.MeshBuilder.CreateCylinder("cone",
        {diameterTop: 0, tessellation: 32}, scene);

    var target = new b.Vector3(0, 0, 0);
    target = target.negate();

    var gvec = b.Mesh.CreateLines("gvec", [
        new b.Vector3(0, 0, 0), target
    ], scene);
    gvec.parent = cone;
    gvec.color = new b.Color3(0, 0, 0);

    cone.position = new b.Vector3(0, 1, 0);
    //cone.lookAt(target);
}

function createVector(scene) {
    var gvec = b.Mesh.CreateLines("gvec", [
        new b.Vector3.Zero(), new b.Vector3(0, 2, 0)
    ], scene);
    gvec.color = new b.Color3(0, 0, 0);
}



function createSlab(scene) {
    var slab = b.Mesh.CreateBox("slab", 1.0, scene);
    slab.position = new b.Vector3.Zero();
    slab.scaling.y = 0.1;
    slab.scaling.x = 2;
    // slab.translate(b.Axis.Y, 1, b.Space.WORLD);
    var gvec = b.Mesh.CreateLines("gvec", [
        new b.Vector3.Zero(), new b.Vector3(0, -10, 0)
    ], scene);
    gvec.parent = slab;
    gvec.color = new b.Color3(0, 0, 0);

}

function createScene() {
    var scene = new b.Scene(engine);

    scene.clearColor = new b.Color3(0.7, 0.75, 0.7);

    var camera = new b.ArcRotateCamera("arc_cam", 0, 0, 0,
        b.Vector3.Zero(), scene);

    camera.setTarget(b.Vector3.Zero());
    //camera.setPosition(new b.Vector3(5, 5, 5));
    camera.setPosition(new b.Vector3(0, 2, -4));
    camera.attachControl(canvas, false);

    var light0 = new b.HemisphericLight("hemi0",
        new b.Vector3(0, 1, 0), scene);

    light0.intensity = 0.5;

    createVector(scene);
    //createSlab(scene);
    // createCone(scene);
    createAxes(10, scene);
    return scene;
}

var y_rot = 0;

scene = createScene();

// Register a render loop to repeatedly render the scene
engine.runRenderLoop(function() {

    var target = new b.Vector3(0, 1, 1);
    var vec = scene.getMeshByName('gvec');

    vec.rotate()
    //scene.getMeshByName('slab').rotate(b.Axis.X, 0.01, BABYLON.Space.WORLD);
    // scene.getMeshByName('slab').rotation.y = y_rot, BABYLON.Space.WORLD;
    scene.render();
});

var socket = io.connect();

socket.on('connect', function() {
    console.log("connected from the client side");

    socket.on('sample', function(data) {
        sample = JSON.parse(data);
        y_rot = sample.v[1];
    });

    socket.on('disconnect', function() {
        console.log('server disconnected');
    });
    // socket.disconnect();
});

  // console.log('connected to server');
  // socket.on('disconnect', function () {
  //   console.log('server disconnected');
  // });
