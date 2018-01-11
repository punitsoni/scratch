var canvas = document.getElementById('renderCanvas');
var scene, camera, renderer;
var t = THREE;

var box, gvec;
var gravity;
init();


function create_axes() {
    var x_geo = new t.Geometry();
    var y_geo = new t.Geometry();
    var z_geo = new t.Geometry();
    x_geo.vertices.push(new t.Vector3(0, 0, 0));
    x_geo.vertices.push(new t.Vector3(100, 0, 0));

    y_geo.vertices.push(new t.Vector3(0, 0, 0));
    y_geo.vertices.push(new t.Vector3(0, 100, 0));

    z_geo.vertices.push(new t.Vector3(0, 0, 0));
    z_geo.vertices.push(new t.Vector3(0, 0, 100));

    x = new t.Line(x_geo, new t.LineBasicMaterial({
              color: 0xFF0000
    }));
    y = new t.Line(y_geo, new t.LineBasicMaterial({
              color: 0x00FF00
    }))
    z = new t.Line(z_geo, new t.LineBasicMaterial({
              color: 0x0000FF
    }))

    scene.add(x);
    scene.add(y);
    scene.add(z);
}

function create_camera() {
    camera = new t.PerspectiveCamera(50,
        window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(10, 5, 10);
    camera.lookAt(new t.Vector3(0, 0, 0));
}

function create_lights() {
    var l0 = new t.AmbientLight(0xffffff, 0.4);
    scene.add(l0);
    var l1 = new t.PointLight(0xffffff, 1);
    l1.position.set(10, 10, 10);
    scene.add(l1);
}

function create_box() {
    var geo = new t.BoxGeometry(1, 1, 1);

    // var material = new t.MeshLambertMaterial({
    //     color: 0xf4d4c4
    // });

    var material = new THREE.MeshPhongMaterial( {
        color: 0x156289,
        // emissive: 0x002233,
        side: THREE.DoubleSide,
        shading: THREE.FlatShading
    } )

    box = new t.Mesh(geo, material);

    box.scale.set(10, 0.5, 5);

    scene.add(box);
}


var Ray = function(origin, direction, length) {
    // var endpoint = origin.clone().add(direction.clone()
    //     .normalize().multiplyScalar(length));
    // var geo = new t.Geometry();
    // geo.vertices.push(origin);
    // geo.vertices.push(endpoint);
    // line = new t.Line(geo, new t.LineBasicMaterial({
    //           color: 0xFFFF00
    // }));
    //scene.add(line);
    this.origin = origin;
    this.line = line;
    this.vector = direction.clone().normalize().multiplyScalar(length)

    this.set_origin = function(origin) {
        this.origin.copy(origin);
        this.__update();
    };

    this.set_direction = function(direction) {
        this.vector = direction.clone().normalize().multiplyScalar(this.vector.length())
        this.__update();
    };

    this.set_length = function(length) {
        this.vector = this.vector.normalize().multiplyScalar(length);
        this.__update();
    };

    this.__update() = function() {
        var endpoint = this.origin.add(this.vector);
        this.line.geometry.vertices[0] = this.origin;
        this.line.geometry.vertices[1] = endpoint;
        this.line.geometry.__dirtyVertices = true;
        this.line.geometry.dynamic = true;
        this.line.geometry.verticesNeedUpdate = true;
    };
}

function create_gvec() {
    var geo = new t.Geometry();
    geo.vertices.push(new t.Vector3(0, 0, 0));
    geo.vertices.push(new t.Vector3(0, 10, 0));
    gvec = new t.Line(geo, new t.LineBasicMaterial({
              color: 0xFFFF00
    }));
    scene.add(gvec);
}

function get_z_from_y(vec_y) {
  return vec_y.applyEuler(new t.Euler(Math.PI/2, 0, 0), 'XYZ');
}

function get_lookat_target(gravity) {
    var y_target = gravity.clone().multiplyScalar(-1).normalize();
    var z_target = y_target.applyEuler(new t.Euler(Math.PI/2, 0, 0), 'XYZ');
    return z_target;
}

function init() {
    scene = new t.Scene();
    renderer = new t.WebGLRenderer({
        canvas: canvas,
        antialias: true
    });
    renderer.setClearColor(0x000000);
    renderer.setSize(window.innerWidth, window.innerHeight);

    create_camera();
    create_axes();
    create_lights();
    create_box();
    create_gvec();

    // r1 = new Ray(new t.Vector3(0, 0, 0),
    //     new t.Vector3(0.2, 1, 0), 5);

    gravity = new t.Vector3(0, -9, 0);
    // setInterval(intake, 30);
    //
    // function intake() {
    //     gravity.set(Math.random(), -9 + Math.random(), Math.random());
    // }


    function update() {
        var target = get_lookat_target(gravity);
        gvec.geometry.vertices[0].set(0, 0, 0);
        gvec.geometry.vertices[1] = gravity.normalize().multiplyScalar(5);
        gvec.geometry.__dirtyVertices = true;
        gvec.geometry.dynamic = true;
        gvec.geometry.verticesNeedUpdate = true;

        //box.up.set(gravity.clone().multiplyScalar(-1));

        var box_y_axis = new t.Vector3(1, 0.5, 0);

        // var box_y_axis = gravity.clone().multiplyScalar(-1).normalize();
        var box_z_axis = get_z_from_y(box_y_axis);
        // box.lookAt(target);
        box.up.copy(box_y_axis);
        box.lookAt(box_z_axis);
    }

    function render() {
        update();
        renderer.render(scene, camera);
        requestAnimationFrame(render);
    }
    render();
}

function truncate_to_2(n) {
  return Math.trunc(n * 100) / 100;
}


var socket = io.connect();

socket.on('connect', function() {
    console.log("connected from the client side");

    socket.on('sample', function(data) {
        sample = JSON.parse(data);
        // gravity.set(sample.v[0], sample.v[1], sample.v[2]);
        gravity.set(truncate_to_2(sample.v[0]),
          truncate_to_2(sample.v[1]),
          truncate_to_2(sample.v[2]));
        console.log(gravity);
    });

    socket.on('disconnect', function() {
        console.log('server disconnected');
    });
});
