/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2026 by Dimitri van Heesch

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

let codefold = {
  opened : true,

  show_plus : function(el) {
    if (el) {
      el.classList.remove('minus');
      el.classList.add('plus');
    }
  },

  show_minus : function(el) {
    if (el) {
      el.classList.add('minus');
      el.classList.remove('plus');
    }
  },

  // toggle all folding blocks
  toggle_all : function() {
    if (this.opened) {
      const foldAll = document.getElementById('fold_all');
      this.show_plus(foldAll);
      document.querySelectorAll('div[id^=foldopen]').forEach(el => el.style.display = 'none');
      document.querySelectorAll('div[id^=foldclosed]').forEach(el => el.style.display = '');
      document.querySelectorAll('div[id^=foldclosed] span.fold').forEach(el => this.show_plus(el));
    } else {
      const foldAll = document.getElementById('fold_all');
      this.show_minus(foldAll);
      document.querySelectorAll('div[id^=foldopen]').forEach(el => el.style.display = '');
      document.querySelectorAll('div[id^=foldclosed]').forEach(el => el.style.display = 'none');
    }
    this.opened=!this.opened;
  },

  // toggle single folding block
  toggle : function(id) {
    const openEl = document.getElementById('foldopen'+id);
    const closedEl = document.getElementById('foldclosed'+id);
    if (openEl) {
      openEl.style.display = openEl.style.display === 'none' ? '' : 'none';
      const nextEl = openEl.nextElementSibling;
      if (nextEl) {
        nextEl.querySelectorAll('span.fold').forEach(el => this.show_plus(el));
      }
    }
    if (closedEl) {
      closedEl.style.display = closedEl.style.display === 'none' ? '' : 'none';
    }
  },

  init : function() {
    // add code folding line and global control
    document.querySelectorAll('span.lineno').forEach((el, index) => {
      el.style.paddingRight = '4px';
      el.style.marginRight = '2px';
      el.style.display = 'inline-block';
      el.style.width = '54px';
      el.style.background = 'linear-gradient(#808080,#808080) no-repeat 46px/2px 100%';
      const span = document.createElement('span');
      if (index === 0) { // add global toggle to first line
        span.className = 'fold minus';
        span.id = 'fold_all';
        span.onclick = () => codefold.toggle_all();
      } else {  // add vertical lines to other rows
        span.className = 'fold'
      }
      el.appendChild(span);
    });
    // add toggle controls to lines with fold divs
    document.querySelectorAll('div.foldopen').forEach(el => {
      // extract specific id to use
      const id = el.getAttribute('id').replace('foldopen','');
      // extract start and end foldable fragment attributes
      const start = el.getAttribute('data-start');
      const end = el.getAttribute('data-end');
      // replace normal fold span with controls for the first line of a foldable fragment
      const firstFold = el.querySelector('span.fold');
      if (firstFold) {
        const span = document.createElement('span');
        span.className = 'fold minus';
        span.onclick = () => codefold.toggle(id);
        firstFold.replaceWith(span);
      }
      // append div for folded (closed) representation
      const closedDiv = document.createElement('div');
      closedDiv.id = 'foldclosed'+id;
      closedDiv.className = 'foldclosed';
      closedDiv.style.display = 'none';
      el.after(closedDiv);
      // extract the first line from the "open" section to represent closed content
      const line = el.children[0] ? el.children[0].cloneNode(true) : null;
      if (line) {
        // remove any glow that might still be active on the original line
        line.classList.remove('glow');
        if (start) {
          // if line already ends with a start marker (e.g. trailing {), remove it
          line.innerHTML = line.innerHTML.replace(new RegExp('\\s*'+start+'\\s*$','g'),'');
        }
        // replace minus with plus symbol
        line.querySelectorAll('span.fold').forEach(span => {
          codefold.show_plus(span);
          // re-apply click handler as it is not copied with cloneNode
          span.onclick = () => codefold.toggle(id);
        });
        // append ellipsis
        const ellipsisLink = document.createElement('a');
        ellipsisLink.href = "javascript:codefold.toggle('"+id+"')";
        ellipsisLink.innerHTML = '&#8230;';
        line.appendChild(document.createTextNode(' '+start));
        line.appendChild(ellipsisLink);
        line.appendChild(document.createTextNode(end));
        // insert constructed line into closed div
        closedDiv.appendChild(line);
      }
    });
  },
};
/* @license-end */
