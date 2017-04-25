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
edges:{smooth: false},
layout:{
randomSeed: undefined,
hierarchical:{
enabled: true,
direction: 'DU'
}
}
};

var nodes = [
{id: 1, label: 'C117', value: 6},
{id: 2, label: 'C182', value: 1},
{id: 3, label: 'C283', value: 6},
{id: 4, label: 'C36', value: 1},
{id: 5, label: 'D122', value: 6},
{id: 6, label: 'F284', value: 1},
{id: 7, label: 'F30', value: 1},
{id: 8, label: 'G85', value: 6},
{id: 9, label: 'G92', value: 6},
{id: 10, label: 'H121', value: 6},
{id: 11, label: 'Y126', value: 6}];

var edges = [
{from: 7, to: 6, color:{color:'green'}, title: 25},
{from: 7, to: 0, color:{color:'red'}, title: -14},
{from: 0, to: 0, color:{color:'red'}, title: -8},
{from: 0, to: 6, color:{color:'red'}, title: -13},
{from: 4, to: 0, color:{color:'red'}, title: -14},
{from: 4, to: 2, color:{color:'green'}, title: 45},
{from: 0, to: 0, color:{color:'red'}, title: -11},
{from: 8, to: 9, color:{color:'green'}, title: 12},
{from: 8, to: 1, color:{color:'green'}, title: 16},
{from: 8, to: 10, color:{color:'green'}, title: 12},
{from: 8, to: 5, color:{color:'green'}, title: 20},
{from: 8, to: 11, color:{color:'green'}, title: 5},
{from: 8, to: 3, color:{color:'green'}, title: 15},
{from: 9, to: 1, color:{color:'green'}, title: 7},
{from: 9, to: 10, color:{color:'green'}, title: 7},
{from: 9, to: 5, color:{color:'green'}, title: 18},
{from: 9, to: 11, color:{color:'green'}, title: 10},
{from: 9, to: 3, color:{color:'green'}, title: 7},
{from: 0, to: 0, color:{color:'red'}, title: -13},
{from: 1, to: 10, color:{color:'green'}, title: 21},
{from: 1, to: 5, color:{color:'green'}, title: 18},
{from: 1, to: 11, color:{color:'green'}, title: 8},
{from: 1, to: 3, color:{color:'green'}, title: 23},
{from: 10, to: 5, color:{color:'green'}, title: 17},
{from: 10, to: 11, color:{color:'green'}, title: 7},
{from: 10, to: 3, color:{color:'green'}, title: 15},
{from: 5, to: 11, color:{color:'green'}, title: 14},
{from: 5, to: 3, color:{color:'green'}, title: 14},
{from: 0, to: 0, color:{color:'red'}, title: -16},
{from: 11, to: 3, color:{color:'green'}, title: 6},
{from: 0, to: 0, color:{color:'red'}, title: -5},
{from: 0, to: 0, color:{color:'red'}, title: -5},
{from: 0, to: 2, color:{color:'red'}, title: -15},
{from: 0, to: 0, color:{color:'red'}, title: -11},
{from: 0, to: 0, color:{color:'red'}, title: -6},
{from: 0, to: 0, color:{color:'red'}, title: -13},
];
