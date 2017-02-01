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
{id: 1, label: 'Comm2', color:{background:'#7fffa1'}},
{id: 2, label: 'Comm3', color:{background:'#7fffa1'}},
{id: 3, label: 'L125', color:{background:'#ffffff'}},
{id: 4, label: 'L273', color:{background:'#ffffff'}},
{id: 5, label: 'L29', color:{background:'#ffffff'}}];

var edges = [
{from: 1, to: 3, color:{color:'red'}, title: -13},
{from: 2, to: 4, color:{color:'red'}, title: -5},
{from: 2, to: 5, color:{color:'red'}, title: -6},
];
