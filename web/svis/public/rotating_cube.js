var canvas = $("#renderCanvas").get(0);
var b = BABYLON;
var engine = new b.Engine(canvas, true);

function createScene() {
    var scene = new b.Scene(engine);

    var createAxes = function(size) {
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

    scene.clearColor = new b.Color3(0.7, 0.7, 0.75);

    var camera = new b.ArcRotateCamera("arc_cam", 0, 0, 0,
        b.Vector3.Zero(), scene);

    camera.setTarget(b.Vector3.Zero());
    //camera.setPosition(new b.Vector3(5, 5, 5));
    camera.setPosition(new b.Vector3(4, 2, 4));
    camera.attachControl(canvas, false);

    var lights = [];

    lights[0] = new b.PointLight("light1", new b.Vector3(10, 10, 10), scene);
    lights[1] = new b.PointLight("light2", new b.Vector3(-10, 10, 10), scene);
    lights[2] = new b.PointLight("light3", new b.Vector3(-10, 10, -10), scene);
    lights[3] = new b.PointLight("light4", new b.Vector3(10, 10, -10), scene);

    for (i = 0; i < 4; i++) {
        lights[i].intensity = 0.4;
    }

    var box = b.Mesh.CreateBox("box", 1.0, scene);

    box.position = new b.Vector3.Zero();

    var matrix = new b.Matrix.TranslationToRef(-0.5, -0.5, -0.5,
        box.getPivotMatrix());

    box.rotate(b.Axis.X, 3 * Math.PI / 4, b.Space.WORLD);
    /* IMP: rotation around Z axis is angle of full cube diagonal */
    box.rotate(b.Axis.Z, -Math.atan2(1, Math.sqrt(2)), b.Space.WORLD);

    var plane = b.Mesh.CreatePlane("plane", 10.0, scene);
    plane.rotation.x = Math.PI/2;

    plane.material = new b.StandardMaterial("m1", scene);
    plane.material.diffuseColor = new BABYLON.Color3(.4, 0.5, 0.3);
    plane.material.specularColor = new BABYLON.Color3(0, 0.1, 0.1);

    // createAxes(10);
    return scene;
}

scene = createScene();

// Register a render loop to repeatedly render the scene
engine.runRenderLoop(function() {
    scene.getMeshByName('box').rotate(b.Axis.Y, 0.01, BABYLON.Space.WORLD);
    scene.render();
});
