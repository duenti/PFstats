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
{id: 1, label: 'A268', value: 1},
{id: 2, label: 'C112', value: 5},
{id: 3, label: 'C118', value: 1},
{id: 4, label: 'C123', value: 10},
{id: 5, label: 'C177', value: 2},
{id: 6, label: 'C271', value: 4},
{id: 7, label: 'C35', value: 3},
{id: 8, label: 'D117', value: 5},
{id: 9, label: 'F272', value: 1},
{id: 10, label: 'F29', value: 1},
{id: 11, label: 'G41', value: 1},
{id: 12, label: 'G83', value: 4},
{id: 13, label: 'G90', value: 1},
{id: 14, label: 'H116', value: 4},
{id: 15, label: 'L276', value: 1}];

var edges = [
{from: 10, to: 9, color:{color:'green'}, title: 21},
{from: 7, to: 4, color:{color:'red'}, title: -16},
{from: 7, to: 5, color:{color:'green'}, title: 34},
{from: 7, to: 15, color:{color:'red'}, title: -13},
{from: 11, to: 4, color:{color:'red'}, title: -13},
{from: 12, to: 2, color:{color:'green'}, title: 16},
{from: 12, to: 8, color:{color:'green'}, title: 18},
{from: 12, to: 4, color:{color:'red'}, title: -26},
{from: 12, to: 6, color:{color:'green'}, title: 15},
{from: 13, to: 8, color:{color:'green'}, title: 15},
{from: 2, to: 14, color:{color:'green'}, title: 18},
{from: 2, to: 8, color:{color:'green'}, title: 17},
{from: 2, to: 4, color:{color:'red'}, title: -37},
{from: 2, to: 6, color:{color:'green'}, title: 24},
{from: 14, to: 8, color:{color:'green'}, title: 14},
{from: 14, to: 4, color:{color:'red'}, title: -24},
{from: 14, to: 6, color:{color:'green'}, title: 15},
{from: 8, to: 4, color:{color:'red'}, title: -28},
{from: 3, to: 4, color:{color:'red'}, title: -13},
{from: 4, to: 5, color:{color:'red'}, title: -15},
{from: 4, to: 1, color:{color:'red'}, title: -15},
{from: 4, to: 6, color:{color:'red'}, title: -37},
];
