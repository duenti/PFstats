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
{id: 1, label: 'A103', color:{background:'#ffffff'}},
{id: 2, label: 'Comm2', color:{background:'#7fffa1'}},
{id: 3, label: 'Comm3', color:{background:'#7fffa1'}},
{id: 4, label: 'K266', color:{background:'#ffffff'}},
{id: 5, label: 'L124', color:{background:'#ffffff'}},
{id: 6, label: 'L272', color:{background:'#ffffff'}},
{id: 7, label: 'L29', color:{background:'#ffffff'}},
{id: 8, label: 'T104', color:{background:'#ffffff'}}];

var edges = [
{from: 2, to: 1, color:{color:'red'}, title: -2},
{from: 2, to: 4, color:{color:'red'}, title: -2},
{from: 2, to: 5, color:{color:'red'}, title: -12},
{from: 2, to: 8, color:{color:'red'}, title: -6},
{from: 3, to: 6, color:{color:'red'}, title: -5},
{from: 3, to: 7, color:{color:'red'}, title: -5},
];
