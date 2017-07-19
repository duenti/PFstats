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
{id: 1, label: 'A84', color:{background:'#ffffff'}},
{id: 2, label: 'Comm2', color:{background:'#7fffa1'}},
{id: 3, label: 'Comm3', color:{background:'#7fffa1'}},
{id: 4, label: 'E264', color:{background:'#ffffff'}},
{id: 5, label: 'G207', color:{background:'#ffffff'}},
{id: 6, label: 'I204', color:{background:'#ffffff'}},
{id: 7, label: 'K114', color:{background:'#ffffff'}},
{id: 8, label: 'K18', color:{background:'#ffffff'}},
{id: 9, label: 'L115', color:{background:'#ffffff'}},
{id: 10, label: 'L4', color:{background:'#ffffff'}},
{id: 11, label: 'N276', color:{background:'#ffffff'}},
{id: 12, label: 'R274', color:{background:'#ffffff'}},
{id: 13, label: 'S31', color:{background:'#ffffff'}},
{id: 14, label: 'T279', color:{background:'#ffffff'}},
{id: 15, label: 'T85', color:{background:'#ffffff'}},
{id: 16, label: 'V115', color:{background:'#ffffff'}},
{id: 17, label: 'V205', color:{background:'#ffffff'}},
{id: 18, label: 'Y284', color:{background:'#ffffff'}}];

var edges = [
{from: 2, to: 10, color:{color:'red'}, title: -25},
{from: 3, to: 11, color:{color:'red'}, title: -170},
{from: 3, to: 18, color:{color:'red'}, title: -72},
{from: 3, to: 12, color:{color:'red'}, title: -52},
{from: 3, to: 13, color:{color:'red'}, title: -72},
{from: 3, to: 14, color:{color:'red'}, title: -129},
{from: 3, to: 15, color:{color:'red'}, title: -140},
{from: 3, to: 16, color:{color:'red'}, title: -36},
{from: 3, to: 17, color:{color:'red'}, title: -66},
{from: 3, to: 5, color:{color:'red'}, title: -68},
{from: 3, to: 1, color:{color:'red'}, title: -80},
{from: 3, to: 4, color:{color:'red'}, title: -88},
{from: 3, to: 9, color:{color:'red'}, title: -95},
{from: 3, to: 6, color:{color:'red'}, title: -34},
{from: 3, to: 7, color:{color:'red'}, title: -38},
{from: 3, to: 8, color:{color:'red'}, title: -115},
];
