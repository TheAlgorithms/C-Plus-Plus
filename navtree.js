/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
 */

function initNavTree(toroot,relpath) {
  let navTreeSubIndices = [];
  const ARROW_DOWN = '&#9660;';
  const ARROW_RIGHT = '&#9658;';
  const NAVPATH_COOKIE_NAME = ''+'navpath';

  const getData = function(varName) {
    const i = varName.lastIndexOf('/');
    const n = i>=0 ? varName.substring(i+1) : varName;
    return eval(n.replace(/-/g,'_'));
  }

  const stripPath = function(uri) {
    return uri.substring(uri.lastIndexOf('/')+1);
  }

  const stripPath2 = function(uri) {
    const i = uri.lastIndexOf('/');
    const s = uri.substring(i+1);
    const m = uri.substring(0,i+1).match(/\/d\w\/d\w\w\/$/);
    return m ? uri.substring(i-6) : s;
  }

  const hashValue = function() {
    return $(location).attr('hash').substring(1).replace(/[^\w-]/g,'');
  }

  const hashUrl = function() {
    return '#'+hashValue();
  }

  const pathName = function() {
    return $(location).attr('pathname').replace(/[^-A-Za-z0-9+&@#/%?=~_|!:,.;()]/g, '');
  }

  const storeLink = function(link) {
    if (!$("#nav-sync").hasClass('sync')) {
      Cookie.writeSetting(NAVPATH_COOKIE_NAME,link,0);
    }
  }

  const deleteLink = function() {
    Cookie.eraseSetting(NAVPATH_COOKIE_NAME);
  }

  const cachedLink = function() {
    return Cookie.readSetting(NAVPATH_COOKIE_NAME,'');
  }

  const getScript = function(scriptName,func) {
    const head = document.getElementsByTagName("head")[0];
    const script = document.createElement('script');
    script.id = scriptName;
    script.type = 'text/javascript';
    script.onload = func;
    script.src = scriptName+'.js';
    head.appendChild(script);
  }

  const createIndent = function(o,domNode,node) {
    let level=-1;
    let n = node;
    while (n.parentNode) { level++; n=n.parentNode; }
    if (node.childrenData) {
      const imgNode = document.createElement("span");
      imgNode.className = 'arrow';
      imgNode.style.paddingLeft=(16*level).toString()+'px';
      imgNode.innerHTML=ARROW_RIGHT;
      node.plus_img = imgNode;
      node.expandToggle = document.createElement("a");
      node.expandToggle.href = "javascript:void(0)";
      node.expandToggle.onclick = function() {
        if (node.expanded) {
          $(node.getChildrenUL()).slideUp("fast");
          node.plus_img.innerHTML=ARROW_RIGHT;
          node.expanded = false;
        } else {
          expandNode(o, node, false, true);
        }
      }
      node.expandToggle.appendChild(imgNode);
      domNode.appendChild(node.expandToggle);
    } else {
      let span = document.createElement("span");
      span.className = 'arrow';
      span.style.width   = 16*(level+1)+'px';
      span.innerHTML = '&#160;';
      domNode.appendChild(span);
    }
  }

  let animationInProgress = false;

  const gotoAnchor = function(anchor,aname) {
    let pos, docContent = $('#doc-content');
    let ancParent = $(anchor.parent());
    if (ancParent.hasClass('memItemLeft') || ancParent.hasClass('memtitle')  ||
        ancParent.hasClass('fieldname')   || ancParent.hasClass('fieldtype') ||
        ancParent.is(':header')) {
      pos = ancParent.position().top;
    } else if (anchor.position()) {
      pos = anchor.position().top;
    }
    if (pos) {
      const dcOffset    = docContent.offset().top;
      const dcHeight    = docContent.height();
      const dcScrHeight = docContent[0].scrollHeight
      const dcScrTop    = docContent.scrollTop();
      let dist = Math.abs(Math.min(pos-dcOffset,dcScrHeight-dcHeight-dcScrTop));
      animationInProgress = true;
      docContent.animate({
        scrollTop: pos + dcScrTop - dcOffset
      },Math.max(50,Math.min(500,dist)),function() {
        window.location.href=aname;
        animationInProgress=false;
      });
    }
  }

  const newNode = function(o, po, text, link, childrenData, lastNode) {
    const node = {
      children     : [],
      childrenData : childrenData,
      depth        : po.depth + 1,
      relpath      : po.relpath,
      isLast       : lastNode,
      li           : document.createElement("li"),
      parentNode   : po,
      itemDiv      : document.createElement("div"),
      labelSpan    : document.createElement("span"),
      label        : document.createTextNode(text),
      expanded     : false,
      childrenUL   : null,
      getChildrenUL : function() {
        if (!this.childrenUL) {
          this.childrenUL = document.createElement("ul");
          this.childrenUL.className = "children_ul";
          this.childrenUL.style.display = "none";
          this.li.appendChild(node.childrenUL);
        }
        return node.childrenUL;
      },
    };

    node.itemDiv.className = "item";
    node.labelSpan.className = "label";
    createIndent(o,node.itemDiv,node);
    node.itemDiv.appendChild(node.labelSpan);
    node.li.appendChild(node.itemDiv);

    const a = document.createElement("a");
    node.labelSpan.appendChild(a);
    po.getChildrenUL().appendChild(node.li);
    a.appendChild(node.label);
    if (link) {
      let url;
      if (link.substring(0,1)=='^') {
        url = link.substring(1);
        link = url;
      } else {
        url = node.relpath+link;
      }
      a.className = stripPath(link.replace('#',':'));
      if (link.indexOf('#')!=-1) {
        const aname = '#'+link.split('#')[1];
        const srcPage = stripPath(pathName());
        const targetPage = stripPath(link.split('#')[0]);
        a.href = srcPage!=targetPage ? url : aname;
        a.onclick = function() {
          storeLink(link);
          aPPar = $(a).parent().parent();
          if (!aPPar.hasClass('selected')) {
            $('.item').removeClass('selected');
            $('.item').removeAttr('id');
            aPPar.addClass('selected');
            aPPar.attr('id','selected');
          }
          const anchor = $(aname);
          gotoAnchor(anchor,aname);
        };
      } else {
        a.href = url;
        a.onclick = () => storeLink(link);
      }
    } else if (childrenData != null) {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
    }
    return node;
  }

  const showRoot = function() {
    const headerHeight = $("#top").height();
    const footerHeight = $("#nav-path").height();
    const windowHeight = $(window).height() - headerHeight - footerHeight;
    (function() { // retry until we can scroll to the selected item
      try {
        const navtree=$('#nav-tree');
        navtree.scrollTo('#selected',100,{offset:-windowHeight/2});
      } catch (err) {
        setTimeout(arguments.callee, 0);
      }
    })();
  }

  const expandNode = function(o, node, imm, setFocus) {
    if (node.childrenData && !node.expanded) {
      if (typeof(node.childrenData)==='string') {
        const varName = node.childrenData;
        getScript(node.relpath+varName,function() {
          node.childrenData = getData(varName);
          expandNode(o, node, imm, setFocus);
        });
      } else {
        if (!node.childrenVisited) {
          getNode(o, node);
        }
        $(node.getChildrenUL()).slideDown("fast");
        node.plus_img.innerHTML = ARROW_DOWN;
        node.expanded = true;
        if (setFocus) {
          $(node.expandToggle).focus();
        }
      }
    }
  }

  const glowEffect = function(n,duration) {
    n.addClass('glow').delay(duration).queue(function(next) {
      $(this).removeClass('glow');next();
    });
  }

  const highlightAnchor = function() {
    const aname = hashUrl();
    const anchor = $(aname);
    if (anchor.parent().attr('class')=='memItemLeft') {
      let rows = $('.memberdecls tr[class$="'+hashValue()+'"]');
      glowEffect(rows.children(),300); // member without details
    } else if (anchor.parent().attr('class')=='fieldname') {
      glowEffect(anchor.parent().parent(),1000); // enum value
    } else if (anchor.parent().attr('class')=='fieldtype') {
      glowEffect(anchor.parent().parent(),1000); // struct field
    } else if (anchor.parent().is(":header")) {
      glowEffect(anchor.parent(),1000); // section header
    } else {
      glowEffect(anchor.next(),1000); // normal member
    }
    gotoAnchor(anchor,aname);
  }

  const selectAndHighlight = function(hash,n) {
    let a;
    if (hash) {
      const link=stripPath(pathName())+':'+hash.substring(1);
      a=$('.item a[class$="'+link+'"]');
    }
    if (a && a.length) {
      a.parent().parent().addClass('selected');
      a.parent().parent().attr('id','selected');
      highlightAnchor();
    } else if (n) {
      $(n.itemDiv).addClass('selected');
      $(n.itemDiv).attr('id','selected');
    }
    let topOffset=5;
    if ($('#nav-tree-contents .item:first').hasClass('selected')) {
      topOffset+=25;
    }
    $('#nav-sync').css('top',topOffset+'px');
    showRoot();
  }

  const showNode = function(o, node, index, hash) {
    if (node && node.childrenData) {
      if (typeof(node.childrenData)==='string') {
        const varName = node.childrenData;
        getScript(node.relpath+varName,function() {
          node.childrenData = getData(varName);
          showNode(o,node,index,hash);
        });
      } else {
        if (!node.childrenVisited) {
          getNode(o, node);
        }
        $(node.getChildrenUL()).css({'display':'block'});
        node.plus_img.innerHTML = ARROW_DOWN;
        node.expanded = true;
        const n = node.children[o.breadcrumbs[index]];
        if (index+1<o.breadcrumbs.length) {
          showNode(o,n,index+1,hash);
        } else if (typeof(n.childrenData)==='string') {
          const varName = n.childrenData;
          getScript(n.relpath+varName,function() {
            n.childrenData = getData(varName);
            node.expanded=false;
            showNode(o,node,index,hash); // retry with child node expanded
          });
        } else {
          const rootBase = stripPath(o.toroot.replace(/\..+$/, ''));
          if (rootBase=="index" || rootBase=="pages" || rootBase=="search") {
            expandNode(o, n, true, false);
          }
          selectAndHighlight(hash,n);
        }
      }
    } else {
      selectAndHighlight(hash);
    }
  }

  const removeToInsertLater = function(element) {
    const parentNode = element.parentNode;
    const nextSibling = element.nextSibling;
    parentNode.removeChild(element);
    return function() {
      if (nextSibling) {
        parentNode.insertBefore(element, nextSibling);
      } else {
        parentNode.appendChild(element);
      }
    };
  }

  const getNode = function(o, po) {
    const insertFunction = removeToInsertLater(po.li);
    po.childrenVisited = true;
    const l = po.childrenData.length-1;
    for (let i in po.childrenData) {
      const nodeData = po.childrenData[i];
      po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2], i==l);
    }
    insertFunction();
  }

  const gotoNode = function(o,subIndex,root,hash,relpath) {
    const nti = navTreeSubIndices[subIndex][root+hash];
    o.breadcrumbs = $.extend(true, [], nti ? nti : navTreeSubIndices[subIndex][root]);
    if (!o.breadcrumbs && root!=NAVTREE[0][1]) { // fallback: show index
      navTo(o,NAVTREE[0][1],"",relpath);
      $('.item').removeClass('selected');
      $('.item').removeAttr('id');
    }
    if (o.breadcrumbs) {
      o.breadcrumbs.unshift(0); // add 0 for root node
      showNode(o, o.node, 0, hash);
    }
  }

  const navTo = function(o,root,hash,relpath) {
    const link = cachedLink();
    if (link) {
      const parts = link.split('#');
      root = parts[0];
      hash = parts.length>1 ? '#'+parts[1].replace(/[^\w-]/g,'') : '';
    }
    if (hash.match(/^#l\d+$/)) {
      const anchor=$('a[name='+hash.substring(1)+']');
      glowEffect(anchor.parent(),1000); // line number
      hash=''; // strip line number anchors
    }
    const url=root+hash;
    let i=-1;
    while (NAVTREEINDEX[i+1]<=url) i++;
    if (i==-1) { i=0; root=NAVTREE[0][1]; } // fallback: show index
    if (navTreeSubIndices[i]) {
      gotoNode(o,i,root,hash,relpath)
    } else {
      getScript(relpath+'navtreeindex'+i,function() {
        navTreeSubIndices[i] = eval('NAVTREEINDEX'+i);
        if (navTreeSubIndices[i]) {
          gotoNode(o,i,root,hash,relpath);
        }
      });
    }
  }

  const showSyncOff = function(n,relpath) {
    n.html('<img src="'+relpath+'sync_off.png" title="'+SYNCOFFMSG+'"/>');
  }

  const showSyncOn = function(n,relpath) {
    n.html('<img src="'+relpath+'sync_on.png" title="'+SYNCONMSG+'"/>');
  }

  const o = {
    toroot : toroot,
    node   : {
      childrenData  : NAVTREE,
      children      : [],
      childrenUL    : document.createElement("ul"),
      getChildrenUL : function() { return this.childrenUL },
      li            : document.getElementById("nav-tree-contents"),
      depth         : 0,
      relpath       : relpath,
      expanded      : false,
      isLast        : true,
      plus_img      : document.createElement("span"),
    },
  };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.plus_img.className = 'arrow';
  o.node.plus_img.innerHTML = ARROW_RIGHT;

  const navSync = $('#nav-sync');
  if (cachedLink()) {
    showSyncOff(navSync,relpath);
    navSync.removeClass('sync');
  } else {
    showSyncOn(navSync,relpath);
  }

  navSync.click(() => {
    const navSync = $('#nav-sync');
    if (navSync.hasClass('sync')) {
      navSync.removeClass('sync');
      showSyncOff(navSync,relpath);
      storeLink(stripPath2(pathName())+hashUrl());
    } else {
      navSync.addClass('sync');
      showSyncOn(navSync,relpath);
      deleteLink();
    }
  });

  navTo(o,toroot,hashUrl(),relpath);
  showRoot();

  $(window).bind('hashchange', () => {
    if (window.location.hash && window.location.hash.length>1) {
      let a;
      if ($(location).attr('hash')) {
        const clslink=stripPath(pathName())+':'+hashValue();
        a=$('.item a[class$="'+clslink.replace(/</g,'\\3c ')+'"]');
      }
      if (a==null || !$(a).parent().parent().hasClass('selected')) {
        $('.item').removeClass('selected');
        $('.item').removeAttr('id');
      }
      const link=stripPath2(pathName());
      navTo(o,link,hashUrl(),relpath);
    } else if (!animationInProgress) {
      $('#doc-content').scrollTop(0);
      $('.item').removeClass('selected');
      $('.item').removeAttr('id');
      navTo(o,toroot,hashUrl(),relpath);
    }
  });

  $("div.toc a[href]").click(function(e) {
    e.preventDefault();
    const aname = $(this).attr("href");
    gotoAnchor($(aname),aname);
  });
}
/* @license-end */
