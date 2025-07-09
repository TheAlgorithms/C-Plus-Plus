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

function initNavTree(toroot,relpath,allMembersFile) {
  let navTreeSubIndices = [];
  const ARROW_DOWN = '<span class="arrowhead opened"></span>';
  const ARROW_RIGHT = '<span class="arrowhead closed"></span>';
  const NAVPATH_COOKIE_NAME = ''+'navpath';
  const fullSidebar = typeof page_layout!=='undefined' && page_layout==1;

  function getScrollBarWidth () {
    let outer = $('<div>').css({visibility: 'hidden', width: 100, overflow: 'scroll', scrollbarWidth: 'thin'}).appendTo('body');
    let widthWithScroll = $('<div>').css({width: '100%'}).appendTo(outer).outerWidth();
    outer.remove();
    return 100 - widthWithScroll;
  }
  const scrollbarWidth = getScrollBarWidth();

  function adjustSyncIconPosition() {
    if (!fullSidebar) {
      const nt = document.getElementById("nav-tree");
      const hasVerticalScrollbar = nt.scrollHeight > nt.clientHeight;
      $("#nav-sync").css({right:parseInt(hasVerticalScrollbar?scrollbarWidth:0)});
    }
  }

  const getData = function(varName) {
    const i = varName.lastIndexOf('/');
    const n = i>=0 ? varName.substring(i+1) : varName;
    const e = n.replace(/-/g,'_');
    return window[e];
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
    script.onload = function() { func(); adjustSyncIconPosition(); }
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
          $(node.getChildrenUL()).slideUp("fast",adjustSyncIconPosition);
          $(node.plus_img.childNodes[0]).removeClass('opened').addClass('closed');
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
      pos = ancParent.offset().top;
    } else if (anchor.position()) {
      pos = anchor.offset().top;
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
        animationInProgress=false;
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
      });
    }
  }

  function htmlToNode(html) {
    const template = document.createElement('template');
    template.innerHTML = html;
    const nNodes = template.content.childNodes.length;
    if (nNodes !== 1) {
        throw new Error(`html parameter must represent a single node; got ${nNodes}. `);
    }
    return template.content.firstChild;
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
    a.appendChild(htmlToNode('<span>'+text+'</span>'));
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
        $(node.getChildrenUL()).slideDown("fast",adjustSyncIconPosition);
        $(node.plus_img.childNodes[0]).addClass('opened').removeClass('closed');
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
        $(node.plus_img.childNodes[0]).removeClass('closed').addClass('opened');
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

  const getNode = function(o, po) {
    po.childrenVisited = true;
    const l = po.childrenData.length-1;
    for (let i in po.childrenData) {
      const nodeData = po.childrenData[i];
      po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2], i==l);
    }
  }

  const gotoNode = function(o,subIndex,root,hash,relpath) {
    const nti = navTreeSubIndices[subIndex][root+hash];
    if (nti==undefined && hash.length>0) { // try root page without hash as fallback
      gotoUrl(o,root,'',relpath);
    } else {
      o.breadcrumbs = $.extend(true, [], nti);
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
  }

  const gotoUrl = function(o,root,hash,relpath) {
    const url=root+hash;
    let i=-1;
    while (NAVTREEINDEX[i+1]<=url) i++;
    if (i==-1) { i=0; root=NAVTREE[0][1]; } // fallback: show index
    if (navTreeSubIndices[i]) {
      gotoNode(o,i,root,hash,relpath)
    } else {
      getScript(relpath+'navtreeindex'+i,function() {
        navTreeSubIndices[i] = window['NAVTREEINDEX'+i];
        if (navTreeSubIndices[i]) {
          gotoNode(o,i,root,hash,relpath);
        }
      });
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
    gotoUrl(o,root,hash,relpath);
  }

  const showSyncOff = function(n,relpath) {
    n.html('<div class="nav-sync-icon" title="'+SYNCOFFMSG+'"><span class="sync-icon-left"></span><span class="sync-icon-right"></span></div>');
  }

  const showSyncOn = function(n,relpath) {
    n.html('<div class="nav-sync-icon active" title="'+SYNCONMSG+'"><span class="sync-icon-left"></span><span class="sync-icon-right"></span></div>');
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
    if (!animationInProgress) {
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
        } else {
        $('#doc-content').scrollTop(0);
        $('.item').removeClass('selected');
        $('.item').removeAttr('id');
        navTo(o,toroot,hashUrl(),relpath);
      }
    }
  });

  $(window).resize(function() { adjustSyncIconPosition(); });

  let navtree_trampoline = {
    updateContentTop : function() {}
  }

  function initResizable() {
    let sidenav,mainnav,pagenav,container,navtree,content,header,footer,barWidth=6;
    const RESIZE_COOKIE_NAME = ''+'width';
    const PAGENAV_COOKIE_NAME = ''+'pagenav';
    const fullSidebar = typeof page_layout!=='undefined' && page_layout==1;

    function showHideNavBar() {
      let bar = $('div.sm-dox');
      if (fullSidebar && mainnav && bar) {
        if (mainnav.width()<768) {
          bar.hide();
        } else {
          bar.show();
        }
      }
    }

    function constrainPanelWidths(leftPanelWidth,rightPanelWidth,dragLeft) {
      const contentWidth = container.width()-leftPanelWidth-rightPanelWidth;
      const minContentWidth = 250;
      const minPanelWidth = barWidth;
      if (contentWidth<minContentWidth) // need to shrink panels
      {
        const deficit = minContentWidth - contentWidth;
        if (dragLeft) { // dragging left handle -> try to keep right panel width
          const shrinkLeft = Math.min(deficit, leftPanelWidth-minPanelWidth);
          leftPanelWidth -= shrinkLeft;
          const remainingDeficit = deficit - shrinkLeft;
          const shrinkRight = Math.min(remainingDeficit, rightPanelWidth-minPanelWidth);
          rightPanelWidth -= shrinkRight;
        } else { // dragging right handle -> try to keep left panel width
          const shrinkRight = Math.min(deficit, rightPanelWidth-minPanelWidth);
          rightPanelWidth -= shrinkRight;
          const remainingDeficit = deficit - shrinkRight;
          const shrinkLeft = Math.min(remainingDeficit, leftPanelWidth-minPanelWidth);
          leftPanelWidth -= shrinkLeft;
        }
      } else {
        rightPanelWidth = pagenav.length ? Math.max(minPanelWidth,rightPanelWidth) : 0;
        leftPanelWidth = Math.max(minPanelWidth,leftPanelWidth);
        }
      return { leftPanelWidth, rightPanelWidth }
    }

    function updateWidths(sidenavWidth,pagenavWidth,dragLeft)
    {
      const widths = constrainPanelWidths(sidenavWidth,pagenavWidth,dragLeft);
      const widthStr = parseInt(widths.leftPanelWidth)+"px";
      content.css({marginLeft:widthStr});
      if (fullSidebar) {
        footer.css({marginLeft:widthStr});
        if (mainnav) {
          mainnav.css({marginLeft:widthStr});
        }
      }
      sidenav.css({width:widthStr});
      if (pagenav.length) {
        container.css({gridTemplateColumns:'auto '+parseInt(widths.rightPanelWidth)+'px'});
        pagenav.css({width:parseInt(widths.rightPanelWidth-1)+'px'});
      }
      return widths;
    }

    function resizeWidth(dragLeft) {
      const sidenavWidth = $(sidenav).outerWidth()-barWidth;
      const pagenavWidth = pagenav.length ? $(pagenav).outerWidth() : 0;
      const widths = updateWidths(sidenavWidth,pagenavWidth,dragLeft);
      Cookie.writeSetting(RESIZE_COOKIE_NAME,widths.leftPanelWidth-barWidth);
      if (pagenav.length) {
        Cookie.writeSetting(PAGENAV_COOKIE_NAME,widths.rightPanelWidth);
      }
    }

    function restoreWidth(sidenavWidth,pagenavWidth) {
      updateWidths(sidenavWidth,pagenavWidth,false);
      showHideNavBar();
    }

    function resizeHeight() {
      const headerHeight = header.outerHeight();
      const windowHeight = $(window).height();
      let contentHeight;
      const footerHeight = footer.outerHeight();
      let navtreeHeight,sideNavHeight;
      if (!fullSidebar) {
        contentHeight = windowHeight - headerHeight - footerHeight - 1;
        navtreeHeight = contentHeight;
        sideNavHeight = contentHeight;
      } else if (fullSidebar) {
        contentHeight = windowHeight - footerHeight - 1;
        navtreeHeight = windowHeight - headerHeight - 1;
        sideNavHeight = windowHeight - 1;
        if (mainnav) {
          contentHeight -= mainnav.outerHeight();
        }
      }
      navtree.css({height:navtreeHeight + "px"});
      sidenav.css({height:sideNavHeight + "px"});
      content.css({height:contentHeight + "px"});
      resizeWidth(false);
      showHideNavBar();
      if (location.hash.slice(1)) {
        (document.getElementById(location.hash.slice(1))||document.body).scrollIntoView();
      }
    }

    header  = $("#top");
    content = $("#doc-content");
    footer  = $("#nav-path");
    sidenav = $("#side-nav");
    if (document.getElementById('main-nav')) {
      mainnav = $("#main-nav");
    }
    navtree = $("#nav-tree");
    pagenav   = $("#page-nav");
    container = $("#container");
    $(".side-nav-resizable").resizable({resize: function(e, ui) { resizeWidth(true); } });
    $(sidenav).resizable({ minWidth: 0 });
    if (pagenav.length) {
      pagehandle  = $("#page-nav-resize-handle");
      pagehandle.on('mousedown touchstart',function(e) { 
         $('body').addClass('resizing');
         pagehandle.addClass('dragging');
         $(document).on('mousemove touchmove',function(e) {
           const clientX = e.clientX || e.originalEvent.touches[0].clientX;
           let pagenavWidth = container[0].offsetWidth-clientX+barWidth/2;
           const sidenavWidth = sidenav.width();
           const widths = constrainPanelWidths(sidenavWidth,pagenavWidth,false);
           container.css({gridTemplateColumns:'auto '+parseInt(widths.rightPanelWidth)+'px'});
           pagenav.css({width:parseInt(widths.rightPanelWidth-1)+'px'});
           content.css({marginLeft:parseInt(widths.leftPanelWidth)+'px'});
           Cookie.writeSetting(PAGENAV_COOKIE_NAME,pagenavWidth);
         });
         $(document).on('mouseup touchend', function(e) {
           $('body').removeClass('resizing');
           pagehandle.removeClass('dragging');
           $(document).off('mousemove mouseup touchmove touchend');
         });
      });
    } else {
      container.css({gridTemplateColumns:'auto'});
    }
    const width = parseInt(Cookie.readSetting(RESIZE_COOKIE_NAME,250));
    const pagenavWidth = parseInt(Cookie.readSetting(PAGENAV_COOKIE_NAME,250));
    if (width) { restoreWidth(width+barWidth,pagenavWidth); } else { resizeWidth(); }
    const url = location.href;
    const i=url.indexOf("#");
    if (i>=0) window.location.hash=url.substr(i);
    const _preventDefault = function(evt) { evt.preventDefault(); };
    $("#splitbar").bind("dragstart", _preventDefault).bind("selectstart", _preventDefault);
    $(window).ready(function() {
      let lastWidth = -1;
      let lastHeight = -1;
      $(window).resize(function() {
          const newWidth  = $(this).width(), newHeight = $(this).height();
          if (newWidth!=lastWidth || newHeight!=lastHeight) {
            resizeHeight();
            navtree_trampoline.updateContentTop();
            lastWidth = newWidth;
            lastHeight = newHeight;
          }
      });
      resizeHeight();
      lastWidth = $(window).width();
      lastHeight = $(window).height();
      content.scroll(function() {
        navtree_trampoline.updateContentTop();
      });
    });
  }


  function initPageToc() {
    const topMapping = [];
    const toc_contents = $('#page-nav-contents');
    const content=$('<ul>').addClass('page-outline');

    var entityMap = {
      '&': '&amp;',
      '<': '&lt;',
      '>': '&gt;',
      '"': '&quot;',
      "'": '&#39;',
      '/': '&#x2F;',
      '`': '&#x60;',
      '=': '&#x3D;'
    };
    function escapeHtml (string) {
      return String(string).replace(/[&<>"'`=\/]/g, function (s) {
        return entityMap[s];
      });
    }

    // for ClassDef/GroupDef/ModuleDef/ConceptDef/DirDef
    const groupSections = [];
    let currentGroup = null;
    $('h2.groupheader, h2.memtitle').each(function(){
      const $element = $(this);
      if ($element.hasClass('groupheader')) {
        currentGroup = { groupHeader: $element, memTitles: [] };
        groupSections.push(currentGroup);
      } else if ($element.hasClass('memtitle') && currentGroup) {
        currentGroup.memTitles.push($element);
      }
    });
    groupSections.forEach(function(item){
      const title = item.groupHeader.text().trim();
      let id = item.groupHeader.attr('id');
      const table = item.groupHeader.parents('table.memberdecls');
      let rows = $();
      if (table.length>0) {
        rows = table.find("tr[class^='memitem:'] td.memItemRight, tr[class^='memitem:'] td.memItemLeft.anon, tr[class=groupHeader] td");
      }
      function hasSubItems() {
        return item.memTitles.length>0 || rows.toArray().some(function(el) { return $(el).is(':visible'); });
      }
      const li = $('<li>').attr('id','nav-'+id);
      const div = $('<div>').addClass('item');
      const span = $('<span>').addClass('arrow').css({ paddingLeft:'0' });
      if (hasSubItems()) {
        span.append($('<span>').addClass('arrowhead opened'));
      }
      const ahref = $('<a>').attr('href','#'+id).append(title);
      content.append(li.append(div.append(span).append(ahref)));
      topMapping.push(id);
      const ulStack = [];
      ulStack.push(content);
      if (hasSubItems()) {
        let last_id = undefined;
        let inMemberGroup = false;
        // declaration sections have rows for items
        rows.each(function(){
          let td = $(this);
          let tr = $(td).parent();
          const is_anon_enum = td.contents().first().text().trim()=='{';
          if (tr.hasClass('template')) {
            tr = tr.prev();
          }
          id = $(tr).attr('id');
          const text = is_anon_enum ? 'anonymous enum' : $(this).find('a:first,b,div.groupHeader').text();
          let isMemberGroupHeader = $(tr).hasClass('groupHeader');
          if ($(tr).is(":visible") && last_id!=id && id!==undefined) {
            if (isMemberGroupHeader && inMemberGroup) {
              ulStack.pop();
              inMemberGroup=false;
            }
            const li2 = $('<li>').attr('id','nav-'+id);
            const div2 = $('<div>').addClass('item');
            const span2 = $('<span>').addClass('arrow').css({ paddingLeft:parseInt(ulStack.length*16)+'px' });
            const ahref = $('<a>').attr('href','#'+id).append(escapeHtml(text));
            li2.append(div2.append(span2).append(ahref));
            topMapping.push(id);
            if (isMemberGroupHeader) {
              span2.append($('<span>').addClass('arrowhead opened'));
              ulStack[ulStack.length-1].append(li2);
              const ul2 = $('<ul>');
              ulStack.push(ul2);
              li2.append(div2).append(ul2);
              inMemberGroup=true;
            } else {
              ulStack[ulStack.length-1].append(li2);
            }
            last_id=id;
          }
        });
        // detailed documentation has h2.memtitle sections for items
        item.memTitles.forEach(function(data) {
          const text = $(data).contents().not($(data).children().first()).text();
          const name = text.replace(/\(\)(\s*\[\d+\/\d+\])?$/, '') // func() [2/8] -> func
          id = $(data).find('span.permalink a').attr('href')
          if (id!==undefined && name!==undefined) {
            const li2 = $('<li>').attr('id','nav-'+id.substring(1));
            const div2 = $('<div>').addClass('item');
            const span2 = $('<span>').addClass('arrow').css({paddingLeft:parseInt(ulStack.length*16)+'px'});
            const ahref = $('<a>').attr('href',id).append(escapeHtml(name));
            ulStack[ulStack.length-1].append(li2.append(div2.append(span2).append(ahref)));
            topMapping.push(id.substring(1));
          }
        });
      }
    });
    if (allMembersFile.length) { // add entry linking to all members page
      const url = location.href;
      let srcBaseUrl = '';
      let dstBaseUrl = '';
      if (relpath.length) { // CREATE_SUBDIRS=YES -> find target location
        srcBaseUrl = url.substring(0, url.lastIndexOf('/')) + '/' + relpath;
        dstBaseUrl = allMembersFile.substr(0, allMembersFile.lastIndexOf('/'))+'/';
      }
      const pageName = url.split('/').pop().split('#')[0].replace(/(\.[^/.]+)$/, '-members$1');
      const li = $('<li>');
      const div = $('<div>').addClass('item');
      const span = $('<span>').addClass('arrow').css({ paddingLeft:'0' });
      const ahref = $('<a>').attr('href',srcBaseUrl+dstBaseUrl+pageName).addClass('noscroll');
      content.append(li.append(div.append(span).append(ahref.append(LISTOFALLMEMBERS))));
    }

    if (groupSections.length==0) {
      // for PageDef
      const sectionTree = [], sectionStack = [];
      $('h1.doxsection, h2.doxsection, h3.doxsection, h4.doxsection, h5.doxsection, h6.doxsection').each(function(){
        const level = parseInt(this.tagName[1]);
        const anchor = $(this).find('a.anchor').attr('id');
        const node = { text: $(this).html(), id: anchor, children: [] };
        while (sectionStack.length && sectionStack[sectionStack.length - 1].level >= level) sectionStack.pop();
        (sectionStack.length ? sectionStack[sectionStack.length - 1].children : sectionTree).push(node);
        sectionStack.push({ ...node, level });
      });
      if (sectionTree.length>0) {
        function render(nodes, level=0) {
          nodes.map(n => {
            const li = $('<li>').attr('id','nav-'+n.id);
            const div = $('<div>').addClass('item');
            const span = $('<span>').addClass('arrow').attr('style','padding-left:'+parseInt(level*16)+'px;');
            if (n.children.length > 0) { span.append($('<span>').addClass('arrowhead opened')); }
            const url = $('<a>').attr('href','#'+n.id);
            content.append(li.append(div.append(span).append(url.append(n.text))));
            topMapping.push(n.id);
            render(n.children,level+1);
          });
        }
        render(sectionTree);
      }
    }

    toc_contents.append(content);

    $(".page-outline a[href]:not(.noscroll)").click(function(e) {
      e.preventDefault();
      const aname = $(this).attr("href");
      gotoAnchor($(aname),aname);
    });

    let lastScrollSourceOffset = -1;
    let lastScrollTargetOffset = -1;
    let lastScrollTargetId = '';

    navtree_trampoline.updateContentTop = function() {
      const pagenavcontents = $("#page-nav-contents");
      if (pagenavcontents.length) {
        const content = $("#doc-content");
        const height = content.height();
        const navy = pagenavcontents.offset().top;
        const yc = content.offset().top;
        let offsets = []
        for (let i=0;i<topMapping.length;i++) {
          const heading = $('#'+topMapping[i]);
          if (heading.parent().hasClass('doxsection')) {
            offsets.push({id:topMapping[i],y:heading.parent().offset().top-yc});
          } else {
            offsets.push({id:topMapping[i],y:heading.offset().top-yc});
          }
        }
        offsets.push({id:'',y:1e10});
        let scrollTarget = undefined, numItems=0;
        for (let i=0;i<topMapping.length;i++) {
          const ys = offsets[i].y;
          const ye = offsets[i+1].y;
          const id = offsets[i].id;
          const nav = $('#nav-'+id);
          const margin = 10; // #pixels before content show as visible
          if ((ys>margin || ye>margin) && (ys<height-margin || ye<height-margin)) {
            if (!scrollTarget) scrollTarget=nav;
            nav.addClass('vis'); // mark navigation entry as visible within content area
            numItems+=1;
          } else {
            nav.removeClass('vis');
          }
        }
        const contentScrollOffset = $('div.contents').offset().top;
        if (scrollTarget && lastScrollTargetId!=scrollTarget.attr('id')) { // new item to scroll to
          const scrollDown = contentScrollOffset<lastScrollSourceOffset;
          const range = 22*numItems;
          const my = range/2-height/2;
          const ulOffset = $('ul.page-outline').offset().top-navy;
          const targetPos=scrollTarget.offset().top-navy-ulOffset;
          const targetOffset=targetPos+my;
          if ( (scrollDown && targetOffset>lastScrollTargetOffset) ||
              (!scrollDown && targetOffset<lastScrollTargetOffset)) 
          { // force panel to scroll in the same direction as content window
            pagenavcontents.stop(); // avoid build-up of history
            pagenavcontents.scrollTo({ left:0, top:targetOffset },{ duration: 500, interrupt: true });
            lastScrollTargetOffset = targetOffset;
          }
          lastScrollTargetId = scrollTarget.attr('id');
        }
        lastScrollSourceOffset = contentScrollOffset;
      }
    }
    // TODO: find out how to avoid a timeout
    setTimeout(() => {
      navtree_trampoline.updateContentTop();
    },200);
  }
  $(document).ready(function() { initPageToc(); initResizable(); });

}
/* @license-end */
