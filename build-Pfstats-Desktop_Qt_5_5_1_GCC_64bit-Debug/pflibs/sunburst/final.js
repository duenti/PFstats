jQuery.fn.d3Click = function () {
  this.each(function (i, e) {
    var evt = new MouseEvent("click");
    e.dispatchEvent(evt);
  });
};

var width = $('#main').width();
var height = ($('#main').width()) * 0.8;
var radius = (Math.min(width, height) / 2) - 10;
var body_width = $('#body').width()


var body_margin_top = d3.select("body").attr("margin-top", height / 60);
var seq_height = d3.select("#sequence").attr("width", body_width);
var seq_height = d3.select("#sequence").attr("height", width * 0.093334);

// Breadcrumb dimensions: width, height, spacing, width of tip/tail.
var b = {
  //w: 75, h: 30, s: 3, t: 10
  w: width / 8, h: 30, s: 3, t: 10
};

var formatNumber = d3.format(",d");

var x = d3.scale.linear()
    .range([0, 2 * Math.PI]);

var y = d3.scale.sqrt()
    .range([0, radius]);

var color = d3.scale.category20c();

var colors1 = {
  "Archea": "#660000",
  "Bacteria": "#666600",
  "Eukaryota": "#000066",
  "Viruses": "#006600",
  "Viroids": "#006666",
  "Other": "#202020"
};

var partition = d3.layout.partition()
    .value(function(d) { return d.size; });

var arc = d3.svg.arc()
    .startAngle(function(d) { return Math.max(0, Math.min(2 * Math.PI, x(d.x))); })
    .endAngle(function(d) { return Math.max(0, Math.min(2 * Math.PI, x(d.x + d.dx))); })
    .innerRadius(function(d) { return Math.max(0, y(d.y)); })
    .outerRadius(function(d) { return Math.max(0, y(d.y + d.dy)); });

var svg = d3.select("#chart").append("svg")
    .attr("width", width)
    .attr("height", height)
    .attr("id", "eita") //comentar
  .append("g")
  .attr("id", "container")
    .attr("transform", "translate(" + width / 2 + "," + (height / 2) + ")");

d3.text("clades.csv", function(text) {
  var csv = d3.csv.parseRows(text);
  var json = buildHierarchy(csv);
  createVisualization(json, csv);
  $("#togglelegend").d3Click();
  zoomFoundLineage('Eukaryota-Metazoa');  
  //$("#").d3Click();
  //falta colorir objeto root de branco aqui
});

/*
function printMe(){
  var valor = $("#querylook").val();
  console.log(valor);
};
*/
function createVisualization(json, csv) {

  var all_lineages = getAllLineages(csv);
  //console.log(all_lineages);
  /*
  d3.select("#querybox").append("input").attr("id", "querylook")
      .attr("type", "text")
      .attr("class","form-control")
      .attr("placeholder", "Input Lineage");

  $( "#querylook" ).autocomplete({
    source: all_lineages
  });
  */
  drawLegend();
  initializeBreadcrumbTrail();
  //make_buttom();
  //var paths = 
  //d3.select("#thebutton").on("click", zoomFoundLineage);
  //d3.select("#thebutton").on("click", printMe);
  //nao sei se funciona
  //<input id='gene_search_box' type="text" class="form-control" placeholder="Input Gene" aria-describedby="sizing-addon2">

  d3.select("#togglelegend").on("click", toggleLegend);
  svg.append("circle")
      .attr("r", radius)
      .style("opacity", 0);
  svg.data([json]).selectAll("path")
      .data(partition.nodes(json))
    .enter().append("path")
      .attr("d", arc)
      //.style("fill", function(d) { return color((d.children ? d : d.parent).name); }) usa escala automatica ordinal de 20 cores diferentes de acordo com os ramos paternos
      .style("fill", function(d) { return d.cor; })
      .style("opacity", 1)
      .on("click", click)
      .on("mouseover", mouseover)
    .append("title")
      //.text(function(d) { return d.name + "\n" + formatNumber(d.value); });
      .text(function(d) { return d.lineage + " \n" + formatNumber(d.value); });
  d3.select("#container").on("mouseleave", mouseleave);
/*  var paths = d3.selectAll("path");
  console.log(paths);*/
  totalSize = svg.node().__data__.value;
};

/*
function make_buttom() {
  var button = d3.select("#querybox").append("button")
          .attr("id", "thebutton")
          .attr("type","button")
          .attr("class","btn-btn")
          .append("div")
          .attr("class","label")
          .text("Buscar");
};
*/
//inicialmente achei que precisa utilizar o centroid e converter os valores por elemento absoluto mas e bem simples
//a funcao d3click recebe um objeto jquery correspondente a um elemento dom e clica nele.
//.each pega cada um dos paths dentro de #eita path
//e a data associada a eles.
//se a data associada a eles e igual a linhagem em querylook
//convertemos this (HTML DOM) para um Jquery Object e invocamos um click nisso
function zoomFoundLineage(linhagem) {
  //var $linhagem = $("#querylook").val(); //pega valor de querylook
  d3.selectAll("#eita path")
  .each(function (d, i) { //para cada elemento path
    if (d.lineage === linhagem ) { //se a linhagem = linhagem achada
      //console.log(d.lineage); //linhagem e impressa
      //var jelm = $(this); //jquery object recebe this do d3, que e um HTML DOM
      //$(jelm).d3Click(); //invoco minha funcao click no DOM.
      svg.transition()
      .duration(400)
      .tween("scale", function() {
        var xd = d3.interpolate(x.domain(), [d.x, d.x + d.dx]),
            yd = d3.interpolate(y.domain(), [d.y, 1]),
            yr = d3.interpolate(y.range(), [d.y ? 20 : 0, radius]);
        return function(t) { x.domain(xd(t)); y.domain(yd(t)).range(yr(t)); };
      })
    .selectAll("path")
      .attrTween("d", function(d) { return function() { return arc(d); }; });
    }
  });
};

function click(d) {
  svg.transition()
      .duration(400)
      .tween("scale", function() {
        var xd = d3.interpolate(x.domain(), [d.x, d.x + d.dx]),
            yd = d3.interpolate(y.domain(), [d.y, 1]),
            yr = d3.interpolate(y.range(), [d.y ? 20 : 0, radius]);
        return function(t) { x.domain(xd(t)); y.domain(yd(t)).range(yr(t)); };
      })
    .selectAll("path")
      .attrTween("d", function(d) { return function() { return arc(d); }; });
}

function mouseover(d) {

  var percentage = (100 * d.value / totalSize).toPrecision(3);
  var percentageString = percentage + "%";
  if (percentage < 0.1) {
    percentageString = "< 0.1%";
  }
  var writeString = percentageString + "of clade: " + d.name + " in this alignment.";
  if (d.name === 'root') {
    writeString = "Root: (Last universal common ancestor).";
  }
  d3.select("#percentage")
      .text(percentageString)
      .text(writeString);

  d3.select("#explanation")
      .style("visibility", "");
  var sequenceArray = getAncestors(d);
  updateBreadcrumbs(sequenceArray, percentageString);
  //below tests to see if it works or not
  console.log(d.name);
  console.log(d.lineage);
  // Fade all the segments.
  d3.selectAll("path")
      .style("opacity", 0.3);

  // Then highlight only those that are an ancestor of the current segment.
  svg.selectAll("path")
      .filter(function(node) {
                return (sequenceArray.indexOf(node) >= 0);
              })
      .style("opacity", 1);
}

// Restore everything to full opacity when moving off the visualization.
function mouseleave(d) {
  // Hide the breadcrumb trail
  d3.select("#trail")
      .style("visibility", "hidden");

  // Deactivate all segments during transition.
  d3.selectAll("path").on("mouseover", null);

  // Transition each segment to full opacity and then reactivate it.
  d3.selectAll("path")
      .transition()
      .duration(10)
      .style("opacity", 1)
      .each("end", function() {
              d3.select(this).on("mouseover", mouseover);
            });

  d3.select("#explanation")
      .style("visibility", "hidden");
}

function initializeBreadcrumbTrail() {
  // Add the svg area.
  var trail = d3.select("#sequence").append("svg")
      .attr("width", width)
      .attr("height", 50)
      .attr("id", "trail");
  // Add the label at the end, for the percentage.
  trail.append("text")
    .attr("id", "endlabel")
    .style("fill", "#000");
}

// Generate a string that describes the points of a breadcrumb polygon.
function breadcrumbPoints(d, i) {
  var points = [];
  points.push("0,0");
  points.push(b.w + ",0");
  points.push(b.w + b.t + "," + (b.h / 2));
  points.push(b.w + "," + b.h);
  points.push("0," + b.h);
  if (i > 0) { // Leftmost breadcrumb; don't include 6th vertex.
    points.push(b.t + "," + (b.h / 2));
  }
  return points.join(" ");
}

// Update the breadcrumb trail to show the current sequence and percentage.
function updateBreadcrumbs(nodeArray, percentageString) {

  // Data join; key function combines name and depth (= position in sequence).
  var g = d3.select("#trail")
      .selectAll("g")
      .data(nodeArray, function(d) { return d.name + d.depth; });

  // Add breadcrumb and label for entering nodes.
  var entering = g.enter().append("g");

  entering.append("polygon")
      .attr("points", breadcrumbPoints)
      //.style("fill", function(d) { return colors[d.name]; });
      //original function above
      .style("fill", function(d) { return d.cor; });
      //uses cor from hiearquical json defined by colorify
      //.style("fill", function(d) { colorify(d.lineage); });
      //.style("fill", function(d) { var s = d.lineage; console.log(s); var cor = colorify(s); return cor; });
      //idk why the above does not work. go figure

  entering.append("text")
      .attr("x", (b.w + b.t) / 2)
      .attr("y", b.h / 2)
      .attr("dy", "0.35em")
      .attr("text-anchor", "middle")
      .text(function(d) { 
        if (d.name.length > 10) {
          return d.name.substring(0,8 ) + '...';
        }
        else {
        return d.name;
        } });

  // Set position for entering and updating nodes.
  g.attr("transform", function(d, i) {
    return "translate(" + i * (b.w + b.s) + ", 0)";
  });

  // Remove exiting nodes.
  g.exit().remove();

  // Now move and update the percentage at the end.
  d3.select("#trail").select("#endlabel")
      .attr("x", (nodeArray.length + 0.5) * (b.w + b.s))
      .attr("y", b.h / 2)
      .attr("dy", "0.35em")
      .attr("text-anchor", "middle")
      .text(percentageString);

  // Make the breadcrumb trail visible, if it's hidden.
  d3.select("#trail")
      .style("visibility", "");

}


function drawLegend() {

  // Dimensions of legend item: width, height, spacing, radius of rounded rect.
  var li = {
    w: 75, h: 30, s: 3, r: 3
  };

  var legend = d3.select("#legend").append("svg")
      .attr("width", li.w)
      .attr("height", d3.keys(colors1).length * (li.h + li.s));

  var g = legend.selectAll("g")
      .data(d3.entries(colors1))
      .enter().append("g")
      .attr("transform", function(d, i) {
              return "translate(0," + i * (li.h + li.s) + ")";
           });

  g.append("rect")
      .attr("rx", li.r)
      .attr("ry", li.r)
      .attr("width", li.w)
      .attr("height", li.h)
      .style("fill", function(d) { return d.value; });

  g.append("text")
      .attr("x", li.w / 2)
      .attr("y", li.h / 2)
      .attr("dy", "0.35em")
      .attr("text-anchor", "middle")
      .text(function(d) { return d.key; });
}

function toggleLegend() {
  var legend = d3.select("#legend");
  if (legend.style("visibility") == "hidden") {
    legend.style("visibility", "");
  } else {
    legend.style("visibility", "hidden");
  }
}

//colors nodes by their lineage
function colorify(lineage) {
  var lineage_array = lineage.split('-');
  var color_input_pal = {
    "Archea" : d3.scale.linear().domain([0, 7]).range(['#660000', '#ff9999']),
    "Bacteria" : d3.scale.linear().domain([0, 7]).range(['#666600', '#ffff99']),
    "Eukaryota" : d3.scale.linear().domain([0, 7]).range(['#000066', '#9999ff']),
    "Viruses" : d3.scale.linear().domain([0, 7]).range(['#006600', '#99ff99']),
    "Viroids" : d3.scale.linear().domain([0, 7]).range(['#006666', '#99ffff']),
    "Other" : d3.scale.linear().domain([0, 7]).range(['#202020', '#e0e0e0'])
  }
  var rgb_string_scale = color_input_pal[lineage_array[0]];
  if (rgb_string_scale == null) {
    rgb_string_scale = color_input_pal["Other"];
    var rgb_color = rgb_string_scale(lineage_array.length);
    return rgb_color;
  }
  var rgb_color = rgb_string_scale(lineage_array.length);
  return rgb_color;
}

//d3.select(self.frameElement).style("height", height + "px");

function getAncestors(node) {
  var path = [];
  var current = node;
  while (current.parent) {
    path.unshift(current);
    current = current.parent;
  }
  return path;
}

function getAllLineages(csv) {
  var root = {"name": "root", "children": []};
  var lineages_list = [];
  var lineages_sizes = {};
  for (var i = 0; i < csv.length; i++) {
    var sequence = csv[i][0];
    var size = +csv[i][1];
    if (isNaN(size)) { // e.g. if this is a header row
      continue;
    }
    var parts = sequence.split("-");
    var currentNode = root;
    for (var j = 0; j < parts.length; j++) {
      var children = currentNode["children"];
      //modifications to save ancestors
      var subarray = parts.slice(0,j+1);
      var lineage = subarray.join('-');
      var nodeName = parts[j];
      var childNode;
      if (j + 1 < parts.length) {
   // Not yet at the end of the sequence; move down the tree.
  var foundChild = false;
  for (var k = 0; k < children.length; k++) {
    if (children[k]["name"] == nodeName) {
      childNode = children[k];
      foundChild = true;
      break;
    }
  }
  // If we don't already have a child node for this branch, create it.
  if (!foundChild) {
    //childNode = {"name": nodeName, "children": []}; //"lineage": lineage };
    childNode = {"name": nodeName, "children": [], "lineage": lineage, "cor": colorify(lineage) };
    //console.log(lineage);
    //console.log(childNode.lineage);
    lineages_list.push(lineage);
    children.push(childNode);
  }
  currentNode = childNode;
      } else {
  // Reached the end of the sequence; create a leaf node.
  //childNode = {"name": nodeName, "size": size}; //"lineage": lineage };
  childNode = {"name": nodeName, "size": size, "lineage": lineage, "cor": colorify(lineage)  };
  //console.log(lineage);
  //console.log(childNode.lineage);
  lineages_list.push(lineage);
  children.push(childNode);
      }
    }
  }
  return lineages_list;//, root;
};

// Take a 2-column CSV and transform it into a hierarchical structure suitable
// for a partition layout. The first column is a sequence of step names, from
// root to leaf, separated by hyphens. The second column is a count of how 
// often that sequence occurred. // "lineage": lineage, "cor": 'white'
function buildHierarchy(csv) {
  var root = {"name": "root", "children": [], "lineage": lineage, "cor": 'white'};
  for (var i = 0; i < csv.length; i++) {
    var sequence = csv[i][0];
    var size = +csv[i][1];
    if (isNaN(size)) { // e.g. if this is a header row
      continue;
    }
    var parts = sequence.split("-");
    var currentNode = root;
    for (var j = 0; j < parts.length; j++) {
      var children = currentNode["children"];
      //modifications to save ancestors
      var subarray = parts.slice(0,j+1);
      var lineage = subarray.join('-');
      var nodeName = parts[j];
      var childNode;
      if (j + 1 < parts.length) {
   // Not yet at the end of the sequence; move down the tree.
  var foundChild = false;
  for (var k = 0; k < children.length; k++) {
    if (children[k]["name"] == nodeName) {
      childNode = children[k];
      foundChild = true;
      break;
    }
  }
  // If we don't already have a child node for this branch, create it.
  if (!foundChild) {
    //childNode = {"name": nodeName, "children": []}; //"lineage": lineage };
    childNode = {"name": nodeName, "children": [], "lineage": lineage, "cor": colorify(lineage) };
    //console.log(lineage);
    //console.log(childNode.lineage);
    children.push(childNode);
  }
  currentNode = childNode;
      } else {
  // Reached the end of the sequence; create a leaf node.
  //childNode = {"name": nodeName, "size": size}; //"lineage": lineage };
  childNode = {"name": nodeName, "size": size, "lineage": lineage, "cor": colorify(lineage)  };
  //console.log(lineage);
  //console.log(childNode.lineage);
  children.push(childNode);
      }
    }
  }
  return root;
};

function test(linhagem){
	alert(linhagem);
};