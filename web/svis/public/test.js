
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
