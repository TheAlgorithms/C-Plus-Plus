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

let initResizableFunc;

function initNavTree(toroot,relpath,allMembersFile) {
  let navTreeSubIndices = [];
  const ARROW_DOWN = '<span class="arrowhead opened"></span>';
  const ARROW_RIGHT = '<span class="arrowhead closed"></span>';
  const NAVPATH_COOKIE_NAME = ''+'navpath';
  const fullSidebar = document.querySelector('meta[name="doxygen-page-layout"]') !== null;

  // Helper functions to replace jQuery
  const $  = (selector) => document.querySelector(selector);
  const $$ = (selector) => Array.from(document.querySelectorAll(selector));
  const hasClass = (el, className) => el ? el.classList.contains(className) : false;
  const offsetTop = (el) => el ? (el.getBoundingClientRect().top + window.pageYOffset) : 0;

  const slideUp = function(el, duration, callback) {
    if (!el) return;
    el.style.overflow = 'hidden';
    el.style.transition = `height ${duration}ms ease`;
    el.style.height = el.scrollHeight + 'px';
    setTimeout(() => {
      el.style.height = '0';
      setTimeout(() => {
        el.style.display = 'none';
        el.style.transition = '';
        el.style.overflow = '';
        el.style.height = '';
        if (callback) callback();
      }, duration);
    }, 10);
  };

  const slideDown = function(el, duration, callback) {
    if (!el) return;
    el.style.display = 'block';
    const height = el.scrollHeight;
    el.style.overflow = 'hidden';
    el.style.height = '0';
    el.style.transition = `height ${duration}ms ease`;
    setTimeout(() => {
      el.style.height = height + 'px';
      setTimeout(() => {
        el.style.transition = '';
        el.style.overflow = '';
        el.style.height = '';
        if (callback) callback();
      }, duration);
    }, 10);
  };

  const animateScrolling = function(el, targetPos, duration, callback) {
    if (!el) return;
    const start = performance.now();
    const startVal = el.scrollTop;
    const tick = (now) => {
      const elapsed  = now - start;
      const progress = Math.min(elapsed / duration, 1);
      const endVal   = targetPos;
      el.scrollTop   = startVal + (endVal - startVal) * progress;

      if (progress < 1) {
        requestAnimationFrame(tick);
      } else if (callback) {
        callback();
      }
    };
    requestAnimationFrame(tick);
  };

  function getScrollBarWidth () {
    const outer = document.createElement('div');
    outer.style.visibility='hidden';
    outer.style.width='100px';
    outer.style.overflow='scroll';
    outer.style.scrollbarWidth='thin';
    document.body.appendChild(outer);

    const inner = document.createElement('div');
    inner.style.width='100%';
    outer.appendChild(inner);

    const widthWithScroll = inner.offsetWidth;
    document.body.removeChild(outer);
    return 100 - widthWithScroll;
  }
  const scrollbarWidth = getScrollBarWidth();

  function adjustSyncIconPosition() {
    if (!fullSidebar) {
      const nt = document.getElementById("nav-tree");
      const hasVerticalScrollbar = nt.scrollHeight > nt.clientHeight;
      const navSync = $("#nav-sync");
      navSync.style.right = (hasVerticalScrollbar ? scrollbarWidth : 0) + 'px';
    }
  }

  const getData = function(varName) {
    const i = varName.lastIndexOf('/');
    const n = i>=0 ? varName.substring(i+1) : varName;
    const e = n.replace(/-/g,'_');
    const r = (e[0] >= '0' && e[0] <= '9') ? '_' + e : e;

    return window[r];
  }

  const stripPath = (uri) => uri.substring(uri.lastIndexOf('/')+1);

  const stripPath2 = function(uri) {
    const i = uri.lastIndexOf('/');
    const s = uri.substring(i+1);
    const m = uri.substring(0,i+1).match(/\/d\w\/d\w\w\/$/);
    return m ? uri.substring(i-6) : s;
  }

  const hashValue = () => location.hash.substring(1).replace(/[^\w-]/g,'');
  const hashUrl = () => '#'+hashValue();
  const pathName = () => location.pathname.replace(/[^-A-Za-z0-9+&@#/%?=~_|!:,.;()]/g, '');

  const storeLink = function(link) {
    const navSync = $("#nav-sync");
    if (!hasClass(navSync, 'sync')) {
      Cookie.writeSetting(NAVPATH_COOKIE_NAME,link,0);
    }
  }

  const deleteLink = function() {
    Cookie.eraseSetting(NAVPATH_COOKIE_NAME);
  }

  const cachedLink = () => Cookie.readSetting(NAVPATH_COOKIE_NAME,'');

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
          slideUp(node.getChildrenUL(), 200, adjustSyncIconPosition);
          const child0 = node.plus_img.childNodes[0]
          if (child0) {
            child0.classList.remove('opened');
            child0.classList.add('closed');
          }
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
      span.style.width = 16*(level+1)+'px';
      span.innerHTML = '&#160;';
      domNode.appendChild(span);
    }
  }

  let animationInProgress = false;

  const gotoAnchor = function(anchor,aname) {
    if (!anchor) return;
    let pos, docContent = $('#doc-content');
    if (!docContent) return;

    const anchorParent = anchor.parentElement;
    if (!anchorParent) return;

    const parentClass = anchorParent.className;
    if (hasClass(anchorParent, 'memItemLeft') || hasClass(anchorParent, 'memtitle') ||
        hasClass(anchorParent, 'fieldname')   || hasClass(anchorParent, 'fieldtype') ||
        anchorParent.tagName.match(/^H[1-6]$/)) {
      pos = offsetTop(anchorParent); // goto anchor's parent
    } else {
      pos = offsetTop(anchor); // goto anchor
    }
    if (pos) {
      const dcOffset    = offsetTop(docContent);
      const dcHeight    = docContent.clientHeight;
      const dcScrHeight = docContent.scrollHeight;
      const dcScrTop    = docContent.scrollTop;
      let dist = Math.abs(Math.min(pos-dcOffset,dcScrHeight-dcHeight-dcScrTop));
      animationInProgress = true;
      animateScrolling(docContent, pos+dcScrTop-dcOffset, Math.max(50,Math.min(500,dist)), function() {
        animationInProgress=false;
        if (parentClass=='memItemLeft') {
          const rows = $$('.memberdecls tr[class$="'+hashValue()+'"]');
          rows.forEach(row => {
            const children = Array.from(row.children);
            children.forEach(child => glowEffect(child, 300));
          });
        } else if (parentClass=='fieldname') {
          glowEffect(anchorParent.parentElement, 1000); // enum value
        } else if (parentClass=='fieldtype') {
          glowEffect(anchorParent.parentElement, 1000); // struct field
        } else if (anchorParent.tagName.match(/^H[1-6]$/)) {
          glowEffect(anchorParent, 1000); // section header
        } else {
          glowEffect(anchor.nextElementSibling, 1000); // normal member
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
          const aPPar = a.parentElement.parentElement;
          if (!hasClass(aPPar, 'selected')) {
            $$('.item').forEach(item => {
              item.classList.remove('selected');
              item.removeAttribute('id');
            });
            aPPar.classList.add('selected');
            aPPar.setAttribute('id', 'selected');
          }
          const anchor = document.querySelector(aname);
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
    const top = $("#top");
    const navPath = $("#nav-path");
    const headerHeight = top ? top.clientHeight : 0;
    const footerHeight = navPath ? navPath.clientHeight : 0;
    const windowHeight = window.innerHeight - headerHeight - footerHeight;
    (function retry() { // retry until we can scroll to the selected item
      try {
        const navtree = $('#nav-tree');
        if (navtree) {
          const selected = navtree.querySelector('#selected');
          if (selected) {
            const offset = -windowHeight/2;
            const targetPos = selected.offsetTop + offset;
            animateScrolling(navtree, Math.max(0, targetPos), 100);
          }
        }
      } catch (err) {
        setTimeout(retry, 0);
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
        slideDown(node.getChildrenUL(), 200, adjustSyncIconPosition);
        const child0 = node.plus_img.childNodes[0]
        if (child0) {
            child0.classList.add('opened');
            child0.classList.remove('closed');
        }
        node.expanded = true;
        if (setFocus) {
          node.expandToggle.focus();
        }
      }
    }
  }

  const glowEffect = function(n, duration) {
    if (!n) return;
    n.classList.add('glow');
    setTimeout(() => {
      n.classList.remove('glow');
    }, duration);
  }

  const highlightAnchor = function() {
    const aname = hashUrl();
    const anchor = document.querySelector(aname);
    gotoAnchor(anchor,aname);
  }

  const selectAndHighlight = function(hash,n) {
    let a;
    if (hash) {
      const link=stripPath(pathName())+':'+hash.substring(1);
      a=document.querySelector('.item a[class$="'+link+'"]');
    }
    if (a) {
      const parent = a.parentElement.parentElement;
      if (parent) {
        parent.classList.add('selected');
        parent.setAttribute('id', 'selected');
      }
      highlightAnchor();
    } else if (n && n.itemDiv) {
      n.itemDiv.classList.add('selected');
      n.itemDiv.setAttribute('id', 'selected');
    }
    let topOffset=5;
    const firstItem = document.querySelector('#nav-tree-contents .item:first-child');
    if (firstItem && hasClass(firstItem, 'selected')) {
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
        const childUL = node.getChildrenUL();
        if (childUL) {
          childUL.style.display='block';
        }
        const child0 = node.plus_img.childNodes[0];
        if (child0) {
          child0.classList.remove('closed');
          child0.classList.add('opened');
        }
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
      o.breadcrumbs = nti ? JSON.parse(JSON.stringify(nti)) : null;
      if (!o.breadcrumbs && root!=NAVTREE[0][1]) { // fallback: show index
        navTo(o,NAVTREE[0][1],"",relpath);
        $$('.item').forEach(item => {
          item.classList.remove('selected');
          item.removeAttribute('id');
        });
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
      const anchor = document.querySelector('a[name='+hash.substring(1)+']');
      if (anchor && anchor.parentElement) {
        glowEffect(anchor.parentElement, 1000); // line number
      }
      hash=''; // strip line number anchors
    }
    gotoUrl(o,root,hash,relpath);
  }

  const showSyncOff = function(n,relpath) {
    if (n) n.innerHTML = '<div class="nav-sync-icon" title="'+SYNCOFFMSG+'"><span class="sync-icon-left"></span><span class="sync-icon-right"></span></div>';
  }

  const showSyncOn = function(n,relpath) {
    if (n) n.innerHTML = '<div class="nav-sync-icon active" title="'+SYNCONMSG+'"><span class="sync-icon-left"></span><span class="sync-icon-right"></span></div>';
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
    navSync.classList.remove('sync');
  } else {
    showSyncOn(navSync,relpath);
  }

  if (navSync) {
    navSync.addEventListener('click', () => {
      const navSync = $('#nav-sync');
      if (hasClass(navSync, 'sync')) {
        navSync.classList.remove('sync');
        showSyncOff(navSync,relpath);
        storeLink(stripPath2(pathName())+hashUrl());
      } else {
        navSync.classList.add('sync');
        showSyncOn(navSync,relpath);
        deleteLink();
      }
    });
  }

  navTo(o,toroot,hashUrl(),relpath);
  showRoot();

  window.addEventListener('hashchange', () => {
    if (!animationInProgress) {
      if (window.location.hash && window.location.hash.length>1) {
        let a;
        if (location.hash) {
          const clslink=stripPath(pathName())+':'+hashValue();
          a=document.querySelector('.item a[class$="'+clslink.replace(/</g,'\\3c ')+'"]');
        }
        if (a==null || !hasClass(a.parentElement.parentElement, 'selected')) {
          $$('.item').forEach(item => {
            item.classList.remove('selected');
            item.removeAttribute('id');
          });
        }
        const link=stripPath2(pathName());
        navTo(o,link,hashUrl(),relpath);
      } else {
        const docContent = $('#doc-content');
        if (docContent) docContent.scrollTop = 0;
        $$('.item').forEach(item => {
          item.classList.remove('selected');
          item.removeAttribute('id');
        });
        navTo(o,toroot,hashUrl(),relpath);
      }
    }
  });

  window.addEventListener('resize', function() { adjustSyncIconPosition(); });

  let navtree_trampoline = {
    updateContentTop : function() {}
  }

  function initResizable() {
    let sidenav,mainnav,pagenav,container,navtree,content,header,footer,barWidth=6;
    const RESIZE_COOKIE_NAME = ''+'width';
    const PAGENAV_COOKIE_NAME = ''+'pagenav';
    const fullSidebar = document.querySelector('meta[name="doxygen-page-layout"]') !== null;

    function showHideNavBar() {
      const bar = document.querySelector('div.sm-dox');
      if (fullSidebar && mainnav && bar) {
        if (mainnav.clientWidth < 768) {
          bar.style.display = 'none';
        } else {
          bar.style.display = '';
        }
      }
    }

    function constrainPanelWidths(leftPanelWidth,rightPanelWidth,dragLeft) {
      const contentWidth = container.clientWidth - leftPanelWidth - rightPanelWidth;
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
        rightPanelWidth = pagenav ? Math.max(minPanelWidth,rightPanelWidth) : 0;
        leftPanelWidth = Math.max(minPanelWidth,leftPanelWidth);
      }
      return { leftPanelWidth, rightPanelWidth }
    }

    function updateWidths(sidenavWidth,pagenavWidth,dragLeft)
    {
      const widths = constrainPanelWidths(sidenavWidth,pagenavWidth,dragLeft);
      const widthStr = parseFloat(widths.leftPanelWidth)+"px";
      content.style.marginLeft = widthStr;
      if (fullSidebar) {
        footer.style.marginLeft = widthStr;
        if (mainnav) {
          mainnav.style.marginLeft = widthStr;
        }
      }
      sidenav.style.width = widthStr;
      if (pagenav) {
        container.style.gridTemplateColumns = 'auto '+parseFloat(widths.rightPanelWidth)+'px';
        if (!dragLeft) {
          pagenav.style.width = parseFloat(widths.rightPanelWidth-1)+'px';
        }
      }
      return widths;
    }

    function resizeWidth(dragLeft) {
      const sidenavWidth = sidenav.offsetWidth - barWidth;
      let pagenavWidth = pagenav ? pagenav.offsetWidth : 0;
      const widths = updateWidths(sidenavWidth,pagenavWidth,dragLeft);
      Cookie.writeSetting(RESIZE_COOKIE_NAME,widths.leftPanelWidth-barWidth);
      if (pagenav) {
        Cookie.writeSetting(PAGENAV_COOKIE_NAME,widths.rightPanelWidth);
      }
    }

    function restoreWidth(sidenavWidth,pagenavWidth) {
      updateWidths(sidenavWidth,pagenavWidth,false);
      showHideNavBar();
    }

    function resizeHeight() {
      const headerHeight = header.offsetHeight;
      const windowHeight = window.innerHeight;
      let contentHeight;
      const footerHeight = footer.offsetHeight;
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
          contentHeight -= mainnav.offsetHeight;
        }
      }
      navtree.style.height = navtreeHeight + "px";
      sidenav.style.height = sideNavHeight + "px";
      content.style.height = contentHeight + "px";
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
    navtree   = $("#nav-tree");
    pagenav   = $("#page-nav");
    container = $("#container");

    // Native JavaScript implementation for resizable side navigation
    const splitbar = $("#splitbar");
    if (splitbar) {
      // Add the ui-resizable-e class to make the splitbar visible and styled correctly
      splitbar.classList.add('ui-resizable-e');
      splitbar.style.zIndex = 90;

      let isResizing = false;
      let startX = 0;
      let startWidth = 0;

      const startResize = (e) => {
        startX = e.clientX ?? e.touches?.[0]?.clientX;
        startWidth = sidenav.offsetWidth - barWidth;
        document.body.classList.add('resizing');
        document.body.style.cursor = 'col-resize';

        const doResize = (e) => {
          const clientX = e.clientX ?? e.touches?.[0]?.clientX;
          if (clientX === undefined) return;
          const delta = clientX - startX;
          const newWidth = startWidth + delta;
          sidenav.style.width = newWidth + 'px';
          resizeWidth(true);
        };

        const stopResize = () => {
          document.body.classList.remove('resizing');
          document.body.style.cursor = 'auto';
          document.removeEventListener('mousemove', doResize);
          document.removeEventListener('touchmove', doResize);
          document.removeEventListener('mouseup',   stopResize);
          document.removeEventListener('touchend',  stopResize);
        };

        document.addEventListener('mousemove', doResize);
        document.addEventListener('touchmove', doResize);
        document.addEventListener('mouseup', stopResize);
        document.addEventListener('touchend', stopResize);
      };

      splitbar.addEventListener('mousedown', startResize);
      splitbar.addEventListener('touchstart', startResize, { passive: false });
    }

    if (pagenav) {
      const pagehandle = $("#page-nav-resize-handle");
      if (pagehandle) {
        const startDrag = (e) => {
          document.body.classList.add('resizing');
          pagehandle.classList.add('dragging');

          const mouseMoveHandler = (e) => {
            const clientX = e.clientX ?? e.touches?.[0]?.clientX;
            if (clientX === undefined) return;
            let pagenavWidth = container.offsetWidth - clientX + barWidth/2;
            const sidenavWidth = sidenav.clientWidth;
            const widths = constrainPanelWidths(sidenavWidth,pagenavWidth,false);
            container.style.gridTemplateColumns = 'auto '+parseFloat(widths.rightPanelWidth)+'px';
            pagenav.style.width = parseFloat(widths.rightPanelWidth-1)+'px';
            content.style.marginLeft = parseFloat(widths.leftPanelWidth - barWidth)+'px';
            Cookie.writeSetting(PAGENAV_COOKIE_NAME,pagenavWidth);
          };

          const mouseUpHandler = (e) => {
            document.body.classList.remove('resizing');
            pagehandle.classList.remove('dragging');
            document.removeEventListener('mousemove', mouseMoveHandler);
            document.removeEventListener('mouseup',   mouseUpHandler);
            document.removeEventListener('touchmove', mouseMoveHandler);
            document.removeEventListener('touchend',  mouseUpHandler);
          };

          document.addEventListener('mousemove', mouseMoveHandler);
          document.addEventListener('touchmove', mouseMoveHandler);
          document.addEventListener('mouseup',   mouseUpHandler);
          document.addEventListener('touchend',  mouseUpHandler);
        };

        pagehandle.addEventListener('mousedown', startDrag);
        pagehandle.addEventListener('touchstart', startDrag, { passive: false });
      }
    } else {
      container.style.gridTemplateColumns = 'auto';
    }
    const width = parseInt(Cookie.readSetting(RESIZE_COOKIE_NAME,250));
    const pagenavWidth = parseInt(Cookie.readSetting(PAGENAV_COOKIE_NAME,250));
    if (width) { restoreWidth(width+barWidth,pagenavWidth); } else { resizeWidth(); }
    const url = location.href;
    const i=url.indexOf("#");
    if (i>=0) window.location.hash=url.substr(i);


    let lastWidth = -1;
    let lastHeight = -1;
    window.addEventListener('resize', function() {
        const newWidth = window.innerWidth;
        const newHeight = window.innerHeight;
        if (newWidth!=lastWidth || newHeight!=lastHeight) {
          resizeHeight();
          navtree_trampoline.updateContentTop();
          lastWidth = newWidth;
          lastHeight = newHeight;
        }
    });
    resizeHeight();
    lastWidth = window.innerWidth;
    lastHeight = window.innerHeight;
    if (content) {
      content.addEventListener('scroll', function() {
        navtree_trampoline.updateContentTop();
      });
    }
  }

  function initPageToc() {
    const topMapping = [];
    const toc_contents = $('#page-nav-contents');
    const content = document.createElement('ul');
    content.className = 'page-outline';

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
    $$('h2.groupheader, h2.memtitle').forEach(function(element){
      if (hasClass(element, 'groupheader')) {
        currentGroup = { groupHeader: element, memTitles: [] };
        groupSections.push(currentGroup);
      } else if (hasClass(element, 'memtitle') && currentGroup) {
        currentGroup.memTitles.push(element);
      }
    });
    groupSections.forEach(function(item){
      const title = item.groupHeader.textContent.trim();
      let id = item.groupHeader.getAttribute('id');
      let table = item.groupHeader.closest('table.memberdecls');
      let rows = [];
      if (table) {
        rows = Array.from(table.querySelectorAll("tr[class^='memitem:'] td.memItemRight, tr[class^='memitem:'] td.memItemLeft.anon, tr[class=groupHeader] td"));
      }
      function hasSubItems() {
        return item.memTitles.length>0 || rows.some(function(el) { 
          return el.offsetParent !== null; // check if visible
        });
      }
      const li = document.createElement('li');
      li.setAttribute('id', 'nav-'+id);
      const div = document.createElement('div');
      div.classList.add('item');
      const span = document.createElement('span');
      span.classList.add('arrow');
      span.style.paddingLeft='0px';
      if (hasSubItems()) {
        const arrowSpan = document.createElement('span');
        arrowSpan.classList.add('arrowhead', 'opened');
        span.appendChild(arrowSpan);
      }
      const ahref = document.createElement('a');
      ahref.setAttribute('href', '#'+id);
      ahref.textContent = title;
      div.appendChild(span);
      div.appendChild(ahref);
      li.appendChild(div);
      content.appendChild(li);
      topMapping.push(id);
      const ulStack = [];
      ulStack.push(content);
      if (hasSubItems()) {
        let last_id = undefined;
        let inMemberGroup = false;
        // declaration sections have rows for items
        rows.forEach(function(td) {
          let tr = td.parentElement;
          const firstChild = td.childNodes[0];
          const is_anon_enum = firstChild && firstChild.textContent.trim()=='{';
          if (hasClass(tr, 'template')) {
            tr = tr.previousElementSibling;
          }
          id = tr.getAttribute('id');
          let text = is_anon_enum ? 'anonymous enum' : (td.querySelector(':first-child') ? td.querySelector(':first-child').textContent : '');
          let isMemberGroupHeader = hasClass(tr, 'groupHeader');
          if (tr.offsetParent !== null && last_id!=id && id!==undefined && id!==null) {
            if (isMemberGroupHeader && inMemberGroup) {
              ulStack.pop();
              inMemberGroup=false;
            }
            const li2 = document.createElement('li');
            li2.setAttribute('id', 'nav-'+id);
            const div2 = document.createElement('div');
            div2.classList.add('item');
            const span2 = document.createElement('span');
            span2.classList.add('arrow');
            span2.style.paddingLeft = parseInt(ulStack.length*16)+'px';
            const ahref = document.createElement('a');
            ahref.setAttribute('href', '#'+id);
            ahref.textContent = escapeHtml(text);
            div2.appendChild(span2);
            div2.appendChild(ahref);
            li2.appendChild(div2);
            topMapping.push(id);
            if (isMemberGroupHeader) {
              const arrowSpan = document.createElement('span');
              arrowSpan.classList.add('arrowhead','opened');
              span2.appendChild(arrowSpan);
              ulStack[ulStack.length-1].appendChild(li2);
              const ul2 = document.createElement('ul');
              ulStack.push(ul2);
              li2.appendChild(ul2);
              inMemberGroup=true;
            } else {
              ulStack[ulStack.length-1].appendChild(li2);
            }
            last_id=id;
          }
        });
        // detailed documentation has h2.memtitle sections for items
        item.memTitles.forEach(function(data) {
          const childNodes = Array.from(data.childNodes);
          const firstChild = data.children[0];
          let text = '';
          childNodes.forEach(node => {
            if (node !== firstChild) {
              text += node.textContent || '';
            }
          });
          const name = text.replace(/\(\)(\s*\[\d+\/\d+\])?$/, '') // func() [2/8] -> func
          const permalinkAnchor = data.querySelector('span.permalink a');
          id = permalinkAnchor ? permalinkAnchor.getAttribute('href') : undefined;
          if (id!==undefined && name!==undefined) {
            const li2 = document.createElement('li');
            li2.setAttribute('id', 'nav-'+id.substring(1));
            const div2 = document.createElement('div');
            div2.classList.add('item');
            const span2 = document.createElement('span');
            span2.classList.add('arrow');
            span2.style.paddingLeft = parseInt(ulStack.length*16)+'px';
            const ahref = document.createElement('a');
            ahref.setAttribute('href', id);
            ahref.textContent = escapeHtml(name);
            div2.appendChild(span2);
            div2.appendChild(ahref);
            li2.appendChild(div2);
            ulStack[ulStack.length-1].appendChild(li2);
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
      const li = document.createElement('li');
      const div = document.createElement('div');
      div.classList.add('item');
      const span = document.createElement('span');
      span.classList.add('arrow');
      span.style.paddingLeft='0px';
      const ahref = document.createElement('a');
      ahref.setAttribute('href', srcBaseUrl+dstBaseUrl+pageName);
      ahref.classList.add('noscroll');
      ahref.textContent = LISTOFALLMEMBERS;
      div.appendChild(span);
      div.appendChild(ahref);
      li.appendChild(div);
      content.appendChild(li);
    }

    if (groupSections.length==0) {
      // for PageDef
      const sectionTree = [], sectionStack = [];
      $$('h1.doxsection, h2.doxsection, h3.doxsection, h4.doxsection, h5.doxsection, h6.doxsection').forEach(function(element){
        const level = parseInt(element.tagName[1]);
        const anchorEl = element.querySelector('a.anchor');
        const anchor = anchorEl ? anchorEl.getAttribute('id') : null;
        // Note: innerHTML is used here to preserve HTML formatting in section headings
        // This content is generated by doxygen, not from user input
        const node = { text: element.innerHTML, id: anchor, children: [] };
        while (sectionStack.length && sectionStack[sectionStack.length - 1].level >= level) sectionStack.pop();
        (sectionStack.length ? sectionStack[sectionStack.length - 1].children : sectionTree).push(node);
        sectionStack.push({ ...node, level });
      });
      if (sectionTree.length>0) {
        function render(nodes, level=0) {
          nodes.map(n => {
            const li = document.createElement('li');
            li.setAttribute('id', 'nav-'+n.id);
            const div = document.createElement('div');
            div.classList.add('item');
            const span = document.createElement('span');
            span.classList.add('arrow');
            span.setAttribute('style', 'padding-left:'+parseInt(level*16)+'px;');
            if (n.children.length > 0) {
              const arrowSpan = document.createElement('span');
              arrowSpan.classList.add('arrowhead','opened');
              span.appendChild(arrowSpan);
            }
            const url = document.createElement('a');
            url.setAttribute('href', '#'+n.id);
            // innerHTML used to preserve HTML formatting from doxygen-generated content
            url.innerHTML = n.text;
            div.appendChild(span);
            div.appendChild(url);
            li.appendChild(div);
            content.appendChild(li);
            topMapping.push(n.id);
            render(n.children,level+1);
          });
        }
        render(sectionTree);
      }
    }

    if (toc_contents) {
      toc_contents.appendChild(content);
    }

    $$(".page-outline a[href]:not(.noscroll)").forEach(function(anchor) {
      anchor.addEventListener('click', function(e) {
        e.preventDefault();
        const aname = this.getAttribute("href");
        gotoAnchor(document.querySelector(aname), aname);
      });
    });

    let lastScrollSourceOffset = -1;
    let lastScrollTargetOffset = -1;
    let lastScrollTargetId = '';

    navtree_trampoline.updateContentTop = function() {
      const pagenavcontents = $("#page-nav-contents");
      if (pagenavcontents) {
        const content = $("#doc-content");
        const height = content ? content.clientHeight : 0;
        const navy = pagenavcontents ? offsetTop(pagenavcontents) : 0;
        const yc = content ? offsetTop(content) : 0;
        let offsets = []
        for (let i=0;i<topMapping.length;i++) {
          const heading = document.getElementById(topMapping[i]);
          if (heading && heading.parentElement && hasClass(heading.parentElement, 'doxsection')) {
            offsets.push({id:topMapping[i],y:offsetTop(heading.parentElement)-yc});
          } else if (heading) {
            offsets.push({id:topMapping[i],y:offsetTop(heading)-yc});
          }
        }
        offsets.push({id:'',y:1e10});
        let scrollTarget = undefined, numItems=0;
        for (let i=0;i<offsets.length-1;i++) {
          const ys = offsets[i].y;
          const ye = offsets[i+1].y;
          const id = offsets[i].id;
          const nav = document.getElementById('nav-'+id);
          const margin = 10; // #pixels before content show as visible
          if ((ys>margin || ye>margin) && (ys<height-margin || ye<height-margin)) {
            if (!scrollTarget) scrollTarget=nav;
            if (nav) nav.classList.add('vis'); // mark navigation entry as visible within content area
            numItems+=1;
          } else {
            if (nav) nav.classList.remove('vis');
          }
        }
        const contentsDiv = document.querySelector('div.contents');
        const contentScrollOffset = contentsDiv ? offsetTop(contentsDiv) : 0;
        if (scrollTarget && lastScrollTargetId!=scrollTarget.getAttribute('id')) { // new item to scroll to
          const scrollDown = contentScrollOffset<lastScrollSourceOffset;
          const range = 22*numItems;
          const my = range/2-height/2;
          const pageOutline = document.querySelector('ul.page-outline');
          const ulOffset = pageOutline ? offsetTop(pageOutline)-navy : 0;
          const targetPos = offsetTop(scrollTarget)-navy-ulOffset;
          const targetOffset=targetPos+my;
          if ( (scrollDown && targetOffset>lastScrollTargetOffset) ||
              (!scrollDown && targetOffset<lastScrollTargetOffset)) 
          { // force panel to scroll in the same direction as content window
            if (pagenavcontents) {
              pagenavcontents.scrollTo({
                left: 0,
                top: targetOffset,
                behavior: 'smooth'
              });
            }
            lastScrollTargetOffset = targetOffset;
          }
          lastScrollTargetId = scrollTarget.getAttribute('id');
        }
        lastScrollSourceOffset = contentScrollOffset;
      }
    }
    // TODO: find out how to avoid a timeout
    setTimeout(() => {
      navtree_trampoline.updateContentTop();
    },200);
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', function() {
      initPageToc();
      initResizable();
    });
  } else {
    initPageToc();
    initResizable();
  }

  initResizableFunc = initResizable;

}
/* @license-end */
