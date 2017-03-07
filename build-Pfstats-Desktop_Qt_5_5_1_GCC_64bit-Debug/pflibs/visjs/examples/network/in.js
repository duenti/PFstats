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
randomSeed: undefined
}
};

var nodes = [
{id: 1, label: 'D107', value: 4},
{id: 2, label: 'D118', value: 2},
{id: 3, label: 'D177', value: 1},
{id: 4, label: 'D182', value: 1},
{id: 5, label: 'D183', value: 1},
{id: 6, label: 'D234', value: 1},
{id: 7, label: 'D58', value: 2},
{id: 8, label: 'F211', value: 10},
{id: 9, label: 'G59', value: 1},
{id: 10, label: 'G62', value: 2},
{id: 11, label: 'H76', value: 3},
{id: 12, label: 'L102', value: 2},
{id: 13, label: 'L57', value: 1},
{id: 14, label: 'L65', value: 1},
{id: 15, label: 'N106', value: 1},
{id: 16, label: 'N154', value: 2},
{id: 17, label: 'N68', value: 1},
{id: 18, label: 'N89', value: 1},
{id: 19, label: 'S107', value: 2},
{id: 20, label: 'S64', value: 2},
{id: 21, label: 'T98', value: 1},
{id: 22, label: 'V197', value: 5},
{id: 23, label: 'W224', value: 1}];

var edges = [
{from: 13, to: 8, color:{color:'red'}, title: -5},
{from: 7, to: 1, color:{color:'red'}, title: -6},
{from: 7, to: 8, color:{color:'red'}, title: -12},
{from: 9, to: 8, color:{color:'red'}, title: -6},
{from: 10, to: 1, color:{color:'red'}, title: -8},
{from: 10, to: 8, color:{color:'red'}, title: -16},
{from: 20, to: 22, color:{color:'green'}, title: 15},
{from: 20, to: 8, color:{color:'red'}, title: -14},
{from: 14, to: 16, color:{color:'green'}, title: 5},
{from: 17, to: 11, color:{color:'red'}, title: -5},
{from: 11, to: 19, color:{color:'red'}, title: -5},
{from: 11, to: 22, color:{color:'red'}, title: -5},
{from: 18, to: 8, color:{color:'red'}, title: -5},
{from: 21, to: 8, color:{color:'red'}, title: -8},
{from: 12, to: 19, color:{color:'red'}, title: -6},
{from: 12, to: 6, color:{color:'red'}, title: -5},
{from: 15, to: 23, color:{color:'green'}, title: 6},
{from: 1, to: 2, color:{color:'red'}, title: -10},
{from: 1, to: 22, color:{color:'red'}, title: -7},
{from: 2, to: 8, color:{color:'red'}, title: -8},
{from: 16, to: 8, color:{color:'red'}, title: -13},
{from: 3, to: 22, color:{color:'red'}, title: -6},
{from: 4, to: 5, color:{color:'green'}, title: 18},
{from: 22, to: 8, color:{color:'red'}, title: -12},
];
