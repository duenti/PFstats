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
{id: 1, label: 'A268', value: 2},
{id: 2, label: 'C118', value: 1},
{id: 3, label: 'C177', value: 1},
{id: 4, label: 'C262', value: 2},
{id: 5, label: 'C264', value: 2},
{id: 6, label: 'C35', value: 1},
{id: 7, label: 'D117', value: 2},
{id: 8, label: 'D265', value: 2},
{id: 9, label: 'F272', value: 2},
{id: 10, label: 'F29', value: 2},
{id: 11, label: 'G144', value: 1},
{id: 12, label: 'G83', value: 1},
{id: 13, label: 'G90', value: 1},
{id: 14, label: 'L124', value: 1},
{id: 15, label: 'T104', value: 1}];

var edges = [
{from: 10, to: 1, color:{color:'green'}, title: 15},
{from: 10, to: 9, color:{color:'green'}, title: 19},
{from: 6, to: 3, color:{color:'green'}, title: 28},
{from: 12, to: 7, color:{color:'green'}, title: 11},
{from: 13, to: 7, color:{color:'green'}, title: 11},
{from: 15, to: 14, color:{color:'green'}, title: 17},
{from: 2, to: 11, color:{color:'green'}, title: 19},
{from: 4, to: 5, color:{color:'green'}, title: 12},
{from: 4, to: 8, color:{color:'green'}, title: 10},
{from: 5, to: 8, color:{color:'green'}, title: 12},
{from: 1, to: 9, color:{color:'green'}, title: 18},
];