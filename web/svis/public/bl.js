var canvas = $("#renderCanvas").get(0);
var engine = new BABYLON.Engine(canvas, true);
var scene = new BABYLON.Scene(engine);

var b = BABYLON

var showAxes = function(size) {
    var axisX = BABYLON.Mesh.CreateLines("axisX", [
        new BABYLON.Vector3.Zero(), new BABYLON.Vector3(size, 0, 0)], scene);
    axisX.color = new BABYLON.Color3(1, 0, 0);
    var axisY = BABYLON.Mesh.CreateLines("axisY", [
        new BABYLON.Vector3.Zero(), new BABYLON.Vector3(0, size, 0)], scene);
    axisY.color = new BABYLON.Color3(0, 1, 0);
    var axisZ = BABYLON.Mesh.CreateLines("axisZ", [
        new BABYLON.Vector3.Zero(), new BABYLON.Vector3(0, 0, size)], scene);
    axisZ.color = new BABYLON.Color3(0, 0, 1);
};

var localOrigin;

function createLocalAxes(size) {
    var localX = BABYLON.Mesh.CreateLines("localX", [
      new BABYLON.Vector3.Zero(), new BABYLON.Vector3(size, 0, 0),
      new BABYLON.Vector3(size * 0.95, 0.05 * size, 0),
      new BABYLON.Vector3(size, 0, 0), new BABYLON.Vector3(size * 0.95, -0.05 * size, 0)
      ], scene);
    localX.color = new BABYLON.Color3(1, 0, 0);

    var localY = BABYLON.Mesh.CreateLines("localY", [
        new BABYLON.Vector3.Zero(), new BABYLON.Vector3(0, size, 0),
        new BABYLON.Vector3(-0.05 * size, size * 0.95, 0),
        new BABYLON.Vector3(0, size, 0), new BABYLON.Vector3(0.05 * size, size * 0.95, 0)
	], scene);
    localY.color = new BABYLON.Color3(0, 1, 0);

    var localZ = BABYLON.Mesh.CreateLines("localZ", [
        new BABYLON.Vector3.Zero(), new BABYLON.Vector3(0, 0, size),
        new BABYLON.Vector3( 0 , -0.05 * size, size * 0.95),
        new BABYLON.Vector3(0, 0, size), new BABYLON.Vector3( 0, 0.05 * size, size * 0.95)
        ], scene);
    localZ.color = new BABYLON.Color3(0, 0, 1);

	localOrigin = new BABYLON.Mesh.CreateBox("wlo", 0.5, scene);
	localOrigin.isVisible = false;
	localX.parent = localOrigin;
  	localY.parent = localOrigin;
  	localZ.parent = localOrigin;
}


scene.clearColor = new BABYLON.Color3(0.7, 0.7, 0.75);


var camera = new BABYLON.ArcRotateCamera("arc_cam", 0, 0, 0,
    BABYLON.Vector3.Zero(), scene);

camera.setTarget(BABYLON.Vector3.Zero());
camera.setPosition(new b.Vector3(5, 5, 5));
camera.attachControl(canvas, false);

var lights = [];

lights[0] = new BABYLON.PointLight("light1", new BABYLON.Vector3(10, 10, 10), scene);
lights[1] = new BABYLON.PointLight("light2", new BABYLON.Vector3(-10, 10, 10), scene);
lights[2] = new BABYLON.PointLight("light3", new BABYLON.Vector3(-10, 10, -10), scene);
lights[3] = new BABYLON.PointLight("light4", new BABYLON.Vector3(10, 10, -10), scene);

for (i = 0; i < 4; i++) {
    lights[i].intensity = 0.3 + 0.1 * i;
}


var box = BABYLON.Mesh.CreateBox("box", 1.0, scene);

box.position = new b.Vector3.Zero();


var matrix = new BABYLON.Matrix.TranslationToRef(-0.5, -0.5, -0.5,
    box.getPivotMatrix());

createLocalAxes(1);
showAxes(10);

localOrigin.position = new b.Vector3(1, 1, 1);
localOrigin.rotation.x = Math.PI/2;
localOrigin.rotation.y = Math.PI/4;
localOrigin.isVisible = false;

// box.rotate(new b.Vector3(1, 1, 1), Math.PI/2, b.Space.LOCAL);

box.rotate(b.Axis.X, 3*Math.PI/4, BABYLON.Space.WORLD);
box.rotate(b.Axis.Z, -Math.atan2(1, Math.sqrt(2)), BABYLON.Space.WORLD);

// Register a render loop to repeatedly render the scene
engine.runRenderLoop(function() {
    scene.getMeshByName('box').rotate(b.Axis.Y, 0.01, BABYLON.Space.WORLD);
    scene.render();
});
