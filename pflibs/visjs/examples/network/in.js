var options = {
physics: {
barnesHut: {
gravitationalConstant: -36,
centralGravity: 0.005,
springLength: 230,
springConstant: 0.18
},
maxVelocity: 146,
solver: 'forceAtlas2Based',
timestep: 0.35,
stabilization: {
enabled:true,
iterations:2000,
updateInterval:25
}
},
interaction:{hover:true},
edges:{smooth: false}
};

var nodes = [
{id: 1, label: 'D182', value: 1},
{id: 2, label: 'D183', value: 1},
{id: 3, label: 'G87', value: 1},
{id: 4, label: 'L65', value: 1},
{id: 5, label: 'N106', value: 1},
{id: 6, label: 'N154', value: 1},
{id: 7, label: 'N90', value: 1},
{id: 8, label: 'W224', value: 1}];

var edges = [
{from: 4, to: 6, color:{color:'green'}, title: 5},
{from: 3, to: 7, color:{color:'green'}, title: 19},
{from: 5, to: 8, color:{color:'green'}, title: 6},
{from: 1, to: 2, color:{color:'green'}, title: 18},
];
