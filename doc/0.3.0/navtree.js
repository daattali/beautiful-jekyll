var NAVTREE =
[
  [ "Board", "index.html", [
    [ "Data Structures", "annotated.html", [
      [ "LibBoard::Arrow", "structLibBoard_1_1Arrow.html", null ],
      [ "LibBoard::Board", "classLibBoard_1_1Board.html", null ],
      [ "LibBoard::Circle", "structLibBoard_1_1Circle.html", null ],
      [ "LibBoard::Color", "classLibBoard_1_1Color.html", null ],
      [ "LibBoard::Dot", "structLibBoard_1_1Dot.html", null ],
      [ "LibBoard::Ellipse", "structLibBoard_1_1Ellipse.html", null ],
      [ "LibBoard::GouraudTriangle", "structLibBoard_1_1GouraudTriangle.html", null ],
      [ "LibBoard::Group", "structLibBoard_1_1Group.html", null ],
      [ "LibBoard::Image", "structLibBoard_1_1Image.html", null ],
      [ "LibBoard::Line", "structLibBoard_1_1Line.html", null ],
      [ "LibBoard::MessageStream", "classLibBoard_1_1MessageStream.html", null ],
      [ "LibBoard::Path", "structLibBoard_1_1Path.html", null ],
      [ "LibBoard::Point", "structLibBoard_1_1Point.html", null ],
      [ "LibBoard::Polyline", "structLibBoard_1_1Polyline.html", null ],
      [ "LibBoard::Rect", "structLibBoard_1_1Rect.html", null ],
      [ "LibBoard::Rectangle", "structLibBoard_1_1Rectangle.html", null ],
      [ "LibBoard::Shape", "structLibBoard_1_1Shape.html", null ],
      [ "LibBoard::ShapeList", "structLibBoard_1_1ShapeList.html", null ],
      [ "LibBoard::Board::State", "structLibBoard_1_1Board_1_1State.html", null ],
      [ "LibBoard::Text", "structLibBoard_1_1Text.html", null ],
      [ "LibBoard::Transform", "structLibBoard_1_1Transform.html", null ],
      [ "LibBoard::TransformEPS", "structLibBoard_1_1TransformEPS.html", null ],
      [ "LibBoard::TransformFIG", "structLibBoard_1_1TransformFIG.html", null ],
      [ "LibBoard::TransformSVG", "structLibBoard_1_1TransformSVG.html", null ],
      [ "LibBoard::Triangle", "structLibBoard_1_1Triangle.html", null ]
    ] ],
    [ "Data Structure Index", "classes.html", null ],
    [ "Class Hierarchy", "hierarchy.html", [
      [ "LibBoard::Color", "classLibBoard_1_1Color.html", null ],
      [ "LibBoard::MessageStream", "classLibBoard_1_1MessageStream.html", null ],
      [ "LibBoard::Path", "structLibBoard_1_1Path.html", null ],
      [ "LibBoard::Point", "structLibBoard_1_1Point.html", null ],
      [ "LibBoard::Rect", "structLibBoard_1_1Rect.html", null ],
      [ "LibBoard::Shape", "structLibBoard_1_1Shape.html", [
        [ "LibBoard::Dot", "structLibBoard_1_1Dot.html", null ],
        [ "LibBoard::Ellipse", "structLibBoard_1_1Ellipse.html", [
          [ "LibBoard::Circle", "structLibBoard_1_1Circle.html", null ]
        ] ],
        [ "LibBoard::Line", "structLibBoard_1_1Line.html", [
          [ "LibBoard::Arrow", "structLibBoard_1_1Arrow.html", null ]
        ] ],
        [ "LibBoard::Polyline", "structLibBoard_1_1Polyline.html", [
          [ "LibBoard::GouraudTriangle", "structLibBoard_1_1GouraudTriangle.html", null ],
          [ "LibBoard::Rectangle", "structLibBoard_1_1Rectangle.html", [
            [ "LibBoard::Image", "structLibBoard_1_1Image.html", null ]
          ] ],
          [ "LibBoard::Triangle", "structLibBoard_1_1Triangle.html", null ]
        ] ],
        [ "LibBoard::ShapeList", "structLibBoard_1_1ShapeList.html", [
          [ "LibBoard::Board", "classLibBoard_1_1Board.html", null ],
          [ "LibBoard::Group", "structLibBoard_1_1Group.html", null ]
        ] ],
        [ "LibBoard::Text", "structLibBoard_1_1Text.html", null ]
      ] ],
      [ "LibBoard::Board::State", "structLibBoard_1_1Board_1_1State.html", null ],
      [ "LibBoard::Transform", "structLibBoard_1_1Transform.html", [
        [ "LibBoard::TransformEPS", "structLibBoard_1_1TransformEPS.html", null ],
        [ "LibBoard::TransformFIG", "structLibBoard_1_1TransformFIG.html", null ],
        [ "LibBoard::TransformSVG", "structLibBoard_1_1TransformSVG.html", null ]
      ] ]
    ] ],
    [ "Data Fields", "functions.html", null ],
    [ "Namespace List", "namespaces.html", [
      [ "LibBoard", "namespaceLibBoard.html", null ],
      [ "LibBoard::Fonts", "namespaceLibBoard_1_1Fonts.html", null ]
    ] ],
    [ "Namespace Members", "namespacemembers.html", null ],
    [ "File List", "files.html", [
      [ "Board.cpp", "Board_8cpp.html", null ],
      [ "Board.h", "Board_8h.html", null ],
      [ "Color.cpp", "Color_8cpp.html", null ],
      [ "Color.h", "Color_8h.html", null ],
      [ "Path.cpp", "Path_8cpp.html", null ],
      [ "Path.h", "Path_8h.html", null ],
      [ "Point.h", "Point_8h.html", null ],
      [ "PSFonts.cpp", "PSFonts_8cpp.html", null ],
      [ "PSFonts.h", "PSFonts_8h.html", null ],
      [ "Rect.cpp", "Rect_8cpp.html", null ],
      [ "Rect.h", "Rect_8h.html", null ],
      [ "ShapeList.cpp", "ShapeList_8cpp.html", null ],
      [ "ShapeList.h", "ShapeList_8h.html", null ],
      [ "Shapes.cpp", "Shapes_8cpp.html", null ],
      [ "Shapes.h", "Shapes_8h.html", null ],
      [ "Tools.cpp", "Tools_8cpp.html", null ],
      [ "Tools.h", "Tools_8h.html", null ],
      [ "Transforms.cpp", "Transforms_8cpp.html", null ],
      [ "Transforms.h", "Transforms_8h.html", null ]
    ] ],
    [ "Globals", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

