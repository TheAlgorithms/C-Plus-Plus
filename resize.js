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
var once=1;
function initResizable()
{
  var cookie_namespace = 'doxygen';
  var sidenav,navtree,content,header,barWidth=6,desktop_vp=768,titleHeight;

  function readSetting(cookie)
  {
    if (window.chrome) {
      var val = localStorage.getItem(cookie_namespace+'_width');
      if (val) return val;
    } else {
      var myCookie = cookie_namespace+"_"+cookie+"=";
      if (document.cookie) {
        var index = document.cookie.indexOf(myCookie);
        if (index != -1) {
          var valStart = index + myCookie.length;
          var valEnd = document.cookie.indexOf(";", valStart);
          if (valEnd == -1) {
            valEnd = document.cookie.length;
          }
          var val = document.cookie.substring(valStart, valEnd);
          return val;
        }
      }
    }
    return 250;
  }

  function writeSetting(cookie, val)
  {
    if (window.chrome) {
      localStorage.setItem(cookie_namespace+"_width",val);
    } else {
      var date = new Date();
      date.setTime(date.getTime()+(10*365*24*60*60*1000)); // default expiration is one week
      expiration = date.toGMTString();
      document.cookie = cookie_namespace + "_" + cookie + "=" + val + "; SameSite=Lax; expires=" + expiration+"; path=/";
    }
  }

  function resizeWidth()
  {
    var windowWidth = $(window).width() + "px";
    var sidenavWidth = $(sidenav).outerWidth();
    content.css({marginLeft:parseInt(sidenavWidth)+"px"});
    if (typeof page_layout!=='undefined' && page_layout==1) {
      footer.css({marginLeft:parseInt(sidenavWidth)+"px"});
    }
    writeSetting('width',sidenavWidth-barWidth);
  }

  function restoreWidth(navWidth)
  {
    var windowWidth = $(window).width() + "px";
    content.css({marginLeft:parseInt(navWidth)+barWidth+"px"});
    if (typeof page_layout!=='undefined' && page_layout==1) {
      footer.css({marginLeft:parseInt(navWidth)+barWidth+"px"});
    }
    sidenav.css({width:navWidth + "px"});
  }

  function resizeHeight()
  {
    var headerHeight = header.outerHeight();
    var footerHeight = footer.outerHeight();
    var windowHeight = $(window).height();
    var contentHeight,navtreeHeight,sideNavHeight;
    if (typeof page_layout==='undefined' || page_layout==0) { /* DISABLE_INDEX=NO */
      contentHeight = windowHeight - headerHeight - footerHeight;
      navtreeHeight = contentHeight;
      sideNavHeight = contentHeight;
    } else if (page_layout==1) { /* DISABLE_INDEX=YES */
      contentHeight = windowHeight - footerHeight;
      navtreeHeight = windowHeight - headerHeight;
      sideNavHeight = windowHeight;
    }
    content.css({height:contentHeight + "px"});
    navtree.css({height:navtreeHeight + "px"});
    sidenav.css({height:sideNavHeight + "px"});
    if (location.hash.slice(1)) {
      (document.getElementById(location.hash.slice(1))||document.body).scrollIntoView();
    }
  }

  function collapseExpand()
  {
    var newWidth;
    if (sidenav.width()>0) {
      newWidth=0;
    }
    else {
      var width = readSetting('width');
      newWidth = (width>250 && width<$(window).width()) ? width : 250;
    }
    restoreWidth(newWidth);
    var sidenavWidth = $(sidenav).outerWidth();
    writeSetting('width',sidenavWidth-barWidth);
  }

  header  = $("#top");
  sidenav = $("#side-nav");
  content = $("#doc-content");
  navtree = $("#nav-tree");
  footer  = $("#nav-path");
  $(".side-nav-resizable").resizable({resize: function(e, ui) { resizeWidth(); } });
  $(sidenav).resizable({ minWidth: 0 });
  $(window).resize(function() { resizeHeight(); });
  var device = navigator.userAgent.toLowerCase();
  var touch_device = device.match(/(iphone|ipod|ipad|android)/);
  if (touch_device) { /* wider split bar for touch only devices */
    $(sidenav).css({ paddingRight:'20px' });
    $('.ui-resizable-e').css({ width:'20px' });
    $('#nav-sync').css({ right:'34px' });
    barWidth=20;
  }
  var width = readSetting('width');
  if (width) { restoreWidth(width); } else { resizeWidth(); }
  resizeHeight();
  var url = location.href;
  var i=url.indexOf("#");
  if (i>=0) window.location.hash=url.substr(i);
  var _preventDefault = function(evt) { evt.preventDefault(); };
  $("#splitbar").bind("dragstart", _preventDefault).bind("selectstart", _preventDefault);
  if (once) {
    $(".ui-resizable-handle").dblclick(collapseExpand);
    once=0
  }
  $(window).on('load',resizeHeight);
}
/* @license-end */
