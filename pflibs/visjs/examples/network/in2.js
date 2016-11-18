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
{id: 1, label: 'Comm12', color:{background:'#7fffa1'}},
{id: 2, label: 'Comm13', color:{background:'#7fffa1'}},
{id: 3, label: 'Comm6', color:{background:'#7fffa1'}},
{id: 4, label: 'Comm9', color:{background:'#7fffa1'}},
{id: 5, label: 'D639', color:{background:'#ffffff'}},
{id: 6, label: 'I626', color:{background:'#ffffff'}},
{id: 7, label: 'L607', color:{background:'#ffffff'}},
{id: 8, label: 'R149', color:{background:'#ffffff'}}];

var edges = [
{from: 3, to: 4, color:{color:'red'}, title: -7},
{from: 5, to: 4, color:{color:'red'}, title: -2},
{from: 4, to: 6, color:{color:'red'}, title: -4},
{from: 4, to: 8, color:{color:'red'}, title: -5},
{from: 1, to: 7, color:{color:'red'}, title: -2},
{from: 2, to: 7, color:{color:'red'}, title: -2},
];
