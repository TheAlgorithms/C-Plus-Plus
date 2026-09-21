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
function initMenu(relPath,treeview) {

  const SHOW_DELAY = 250;  // 250ms delay before showing
  const HIDE_DELAY = 500;  // 500ms delay before hiding
  const SLIDE_DELAY = 250; // 250ms slide up/down delay
  const WHEEL_STEP = 30;   // 30 pixel per mouse wheel tick
  const ARROW_STEP = 5;    // 5 pixel when hovering arrow up/down
  const ARROW_POLL_INTERVAL = 20; // 20ms per arrow up/down check
  const MOBILE_WIDTH = 768; // switch point for mobile/desktop mode

  // Helper function for slideDown animation
  function slideDown(element, duration, callback) {
    if (element.dataset.animating) return;
    element.dataset.animating = 'true';

    element.style.removeProperty('display');
    let display = window.getComputedStyle(element).display;
    if (display === 'none') display = 'block';
    element.style.display = display;
    const height = element.offsetHeight;
    element.style.overflow = 'hidden';
    element.style.height = 0;
    element.offsetHeight; // force reflow
    element.style.transitionProperty = 'height';
    element.style.transitionDuration = duration + 'ms';
    element.style.height = height + 'px';
    window.setTimeout(() => {
      element.style.removeProperty('height');
      element.style.removeProperty('overflow');
      element.style.removeProperty('transition-duration');
      element.style.removeProperty('transition-property');
      delete element.dataset.animating;
      if (callback) callback();
    }, duration);
  }

  // Helper function for slideUp animation
  function slideUp(element, duration, callback) {
    if (element.dataset.animating) return;
    element.dataset.animating = 'true';

    element.style.transitionProperty = 'height';
    element.style.transitionDuration = duration + 'ms';
    element.style.height = element.offsetHeight + 'px';
    element.offsetHeight; // force reflow
    element.style.overflow = 'hidden';
    element.style.height = 0;
    window.setTimeout(() => {
      element.style.display = 'none';
      element.style.removeProperty('height');
      element.style.removeProperty('overflow');
      element.style.removeProperty('transition-duration');
      element.style.removeProperty('transition-property');
      delete element.dataset.animating;
      if (callback) callback();
    }, duration);
  }

  // Helper to create the menu tree structure
  function makeTree(data,relPath,topLevel=false) {
    let result='';
    if ('children' in data) {
      if (!topLevel) {
        result+='<ul>';
      }
      for (let i in data.children) {
        let url;
        const link = data.children[i].url;
        if (link.substring(0,1)=='^') {
          url = link.substring(1);
        } else {
          url = relPath+link;
        }
        result+='<li><a href="'+url+'">'+
                                data.children[i].text+'</a>'+
                                makeTree(data.children[i],relPath)+'</li>';
      }
      if (!topLevel) {
        result+='</ul>';
      }
    }
    return result;
  }

  const mainNav = document.getElementById('main-nav');
  if (mainNav && mainNav.children.length > 0) {
    const firstChild = mainNav.children[0];
    firstChild.insertAdjacentHTML('afterbegin', makeTree(menudata, relPath, true));
  }

  const searchBoxPos2 = document.getElementById('searchBoxPos2');
  let searchBoxContents = searchBoxPos2 ? searchBoxPos2.innerHTML : '';
  const mainMenuState = document.getElementById('main-menu-state');
  let prevWidth = 0;

  const initResizableIfExists = function() {
    if (typeof initResizableFunc === 'function') initResizableFunc(treeview);
  }

  // Dropdown menu functionality to replace smartmenus
  let closeAllDropdowns = null; // Will be set by initDropdownMenu

  const isMobile = () => window.innerWidth < MOBILE_WIDTH;

  if (mainMenuState) {
    const mainMenu = document.getElementById('main-menu');
    const searchBoxPos1 = document.getElementById('searchBoxPos1');

    // animate mobile main menu
    mainMenuState.addEventListener('change', function() {
      if (this.checked) {
        slideDown(mainMenu, SLIDE_DELAY, () => {
          mainMenu.style.display = 'block';
          initResizableIfExists();
        });
      } else {
        slideUp(mainMenu, SLIDE_DELAY, () => {
          mainMenu.style.display = 'none';
          initResizableIfExists();
        });
      }
    });

    // set default menu visibility
    const resetState = function() {
      const newWidth = window.innerWidth;
      if (newWidth !== prevWidth) {
        // Close all open dropdown menus when switching between mobile/desktop modes
        if (closeAllDropdowns) {
          closeAllDropdowns();
        }

        if (newWidth < MOBILE_WIDTH) {
          mainMenuState.checked = false;
          mainMenu.style.display = 'none';
          if (searchBoxPos2) {
            searchBoxPos2.innerHTML = '';
            searchBoxPos2.style.display = 'none';
          }
          if (searchBoxPos1) {
            searchBoxPos1.innerHTML = searchBoxContents;
            searchBoxPos1.style.display = '';
          }
        } else {
          mainMenu.style.display = '';
          if (searchBoxPos1) {
            searchBoxPos1.innerHTML = '';
            searchBoxPos1.style.display = 'none';
          }
          if (searchBoxPos2) {
            searchBoxPos2.innerHTML = searchBoxContents;
            searchBoxPos2.style.display = '';
          }
        }
        if (typeof searchBox !== 'undefined') {
          searchBox.CloseResultsWindow();
        }
        prevWidth = newWidth;
      }
    }

    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', function() {
        resetState();
        initResizableIfExists();
      });
    } else {
      resetState();
      initResizableIfExists();
    }
    window.addEventListener('resize', resetState);
  } else {
    initResizableIfExists();
  }

  function initDropdownMenu() {
    const mainMenu = document.getElementById('main-menu');
    if (!mainMenu) return;

    const menuItems = mainMenu.querySelectorAll('li');

    // Helper function to position nested submenu with viewport checking
    function positionNestedSubmenu(submenu, link) {
      const viewport = {
        height: window.innerHeight,
        scrollY: window.scrollY
      };

      // Set initial position - top aligned with parent (next to arrow)
      submenu.style.top = '0';
      if (isMobile()) {
        submenu.style.marginLeft = 0;
      } else {
        submenu.style.marginLeft = link.offsetWidth + 'px';
      }

      // Get submenu dimensions and position
      const submenuRect = submenu.getBoundingClientRect();
      const submenuHeight = submenuRect.height;
      const submenuTop = submenuRect.top;
      const submenuBottom = submenuRect.bottom+1; // add space for border

      // Check if submenu fits in viewport
      const fitsAbove = submenuTop >= 0;
      const fitsBelow = submenuBottom <= viewport.height;

      if (!fitsAbove || !fitsBelow) {
        // Submenu doesn't fit - try to adjust position
        // Overflows bottom, try to shift up
        const overflow = submenuBottom - viewport.height;
        const newTop = Math.max(0, submenuTop-overflow)-submenuTop;
        submenu.style.top = newTop + 'px';

        // Re-check after adjustment
        const adjustedRect = submenu.getBoundingClientRect();
        if (adjustedRect.height > viewport.height) {
          // Still doesn't fit - enable scrolling
          enableSubmenuScrolling(submenu, link);
        }
      }
    }

    // Helper function to enable scrolling for tall submenus
    function enableSubmenuScrolling(submenu, link) {
      // Check if scroll arrows already exist
      if (submenu.dataset.scrollEnabled) return;

      submenu.dataset.scrollEnabled = 'true';

      const viewport = {
        height: window.innerHeight,
        scrollY: window.scrollY
      };

      // Position submenu to fill available viewport space
      const parentRect = link.getBoundingClientRect();
      const availableHeight = viewport.height - 2; // Leave some margin

      submenu.style.maxHeight = availableHeight + 'px';
      submenu.style.overflow = 'hidden';
      submenu.style.position = 'absolute';

      // Create scroll arrows
      const scrollUpArrow = document.createElement('div');
      scrollUpArrow.className = 'submenu-scroll-arrow submenu-scroll-up';
      scrollUpArrow.innerHTML = '<span class="scroll-up-arrow"></span>';//'<span>▲</span>';
      scrollUpArrow.style.cssText = 'position:absolute;top:0;left:0;right:0;height:30px;background:transparent;text-align:center;line-height:30px;color:#fff;cursor:pointer;z-index:1000;display:none;';

      const scrollDownArrow = document.createElement('div');
      scrollDownArrow.className = 'submenu-scroll-arrow submenu-scroll-down';
      scrollDownArrow.innerHTML = '<span class="scroll-down-arrow"></span>';
      scrollDownArrow.style.cssText = 'position:absolute;bottom:0;left:0;right:0;height:30px;background:transparent;text-align:center;line-height:30px;color:#fff;cursor:pointer;z-index:1000;';

      // Create wrapper for submenu content
      const scrollWrapper = document.createElement('div');
      scrollWrapper.className = 'submenu-scroll-wrapper';
      scrollWrapper.style.cssText = 'height:100vh;overflow:hidden;position:relative;';

      // Move submenu children to wrapper
      while (submenu.firstChild) {
        scrollWrapper.appendChild(submenu.firstChild);
      }

      submenu.appendChild(scrollUpArrow);
      submenu.appendChild(scrollWrapper);
      submenu.appendChild(scrollDownArrow);

      let scrollPosition = 0;
      let scrollInterval = null;

      function updateScrollArrows() {
        const maxScroll = scrollWrapper.scrollHeight - availableHeight;
        scrollUpArrow.style.display = scrollPosition > 0 ? 'block' : 'none';
        scrollDownArrow.style.display = scrollPosition < maxScroll ? 'block' : 'none';
      }

      function startScrolling(direction) {
        if (scrollInterval) return;

        scrollInterval = setInterval(() => {
          const maxScroll = scrollWrapper.scrollHeight - availableHeight;

          if (direction === 'up') {
            scrollPosition = Math.max(0, scrollPosition - ARROW_STEP);
          } else {
            scrollPosition = Math.min(maxScroll, scrollPosition + ARROW_STEP);
          }

          scrollWrapper.scrollTop = scrollPosition;
          updateScrollArrows();

          if ((direction === 'up' && scrollPosition === 0) ||
              (direction === 'down' && scrollPosition === maxScroll)) {
            stopScrolling();
          }
        }, ARROW_POLL_INTERVAL);
      }

      function stopScrolling() {
        if (scrollInterval) {
          clearInterval(scrollInterval);
          scrollInterval = null;
        }
      }

      scrollUpArrow.addEventListener('mouseenter', () => startScrolling('up'));
      scrollUpArrow.addEventListener('mouseleave', stopScrolling);
      scrollDownArrow.addEventListener('mouseenter', () => startScrolling('down'));
      scrollDownArrow.addEventListener('mouseleave', stopScrolling);

      function wheelEvent(e) {
        e.preventDefault();
        e.stopPropagation();

        const maxScroll = scrollWrapper.scrollHeight - availableHeight;
        const wheelDelta = e.deltaY;
        const scrollAmount = wheelDelta > 0 ? WHEEL_STEP : -WHEEL_STEP; // Scroll 30px per wheel tick

        scrollPosition = Math.max(0, Math.min(maxScroll, scrollPosition + scrollAmount));
        scrollWrapper.scrollTop = scrollPosition;
        updateScrollArrows();
      }

      // Add mouse wheel scrolling support
      scrollWrapper.addEventListener('wheel', (e) => wheelEvent(e));

      // Also add wheel event to submenu itself to catch events
      submenu.addEventListener('wheel', function(e) {
        // Only handle if scrolling is enabled
        if (submenu.dataset.scrollEnabled) {
          wheelEvent(e);
        }
      });

      // Initial arrow state
      updateScrollArrows();
    }

    // Helper function to clean up scroll arrows
    function disableSubmenuScrolling(submenu) {
      if (!submenu.dataset.scrollEnabled) return;

      delete submenu.dataset.scrollEnabled;

      // Find and remove scroll elements
      const scrollArrows = submenu.querySelectorAll('.submenu-scroll-arrow');
      const scrollWrapper = submenu.querySelector('.submenu-scroll-wrapper');

      if (scrollWrapper) {
        // Move children back to submenu
        while (scrollWrapper.firstChild) {
          submenu.appendChild(scrollWrapper.firstChild);
        }
        scrollWrapper.remove();
      }

      scrollArrows.forEach(arrow => arrow.remove());

      // Reset styles
      submenu.style.maxHeight = '';
      submenu.style.overflow = '';
    }

    menuItems.forEach(item => {
      const submenu = item.querySelector('ul');
      if (submenu) {
        const link = item.querySelector('a');
        if (link) {
          // Add class and ARIA attributes for accessibility
          link.classList.add('has-submenu');
          link.setAttribute('aria-haspopup', 'true');
          link.setAttribute('aria-expanded', 'false');

          // Add sub-arrow indicator
          const span = document.createElement('span');
          span.classList.add('sub-arrow');
          link.append(span);

          // Calculate nesting level for z-index
          // Root menu (main-menu) is level 200 (above the search box at 102),
          // first submenus are level 201, etc.
          let nestingLevel = 200;
          let currentElement = item.parentElement;
          while (currentElement && currentElement.id !== 'main-menu') {
            if (currentElement.tagName === 'UL') {
              nestingLevel++;
            }
            currentElement = currentElement.parentElement;
          }

          // Apply z-index based on nesting level
          // This ensures child menus with shadows appear above parent menus
          submenu.style.zIndex = nestingLevel + 1;

          // Check if this is a level 2+ submenu (nested within another dropdown)
          const isNestedSubmenu = item.parentElement && item.parentElement.id !== 'main-menu';

          // Timeout management for smooth menu navigation
          let showTimeout = null;
          let hideTimeout = null;

          // Desktop: show on hover
          item.addEventListener('mouseenter', function() {
            if (!isMobile()) {
              // Clear any pending hide timeout
              if (hideTimeout) {
                clearTimeout(hideTimeout);
                hideTimeout = null;
              }

              // Set show timeout
              showTimeout = setTimeout(() => {
                // Hide all sibling menus at the same level before showing this one
                const parentElement = item.parentElement;
                if (parentElement) {
                  const siblings = parentElement.querySelectorAll(':scope > li');
                  siblings.forEach(sibling => {
                    if (sibling !== item) {
                      const siblingSubmenu = sibling.querySelector('ul');
                      const siblingLink = sibling.querySelector('a');
                      if (siblingSubmenu && siblingLink) {
                        siblingSubmenu.style.display = 'none';
                        siblingLink.setAttribute('aria-expanded', 'false');
                        disableSubmenuScrolling(siblingSubmenu);
                      }
                    }
                  });
                }

                submenu.style.display = 'block';
                // Only apply positioning for nested submenus (level 2+)
                if (isNestedSubmenu) {
                  positionNestedSubmenu(submenu, link);
                }
                link.setAttribute('aria-expanded', 'true');
                showTimeout = null;
              }, SHOW_DELAY);
            }
          });

          item.addEventListener('mouseleave', function() {
            if (!isMobile()) {
              // Clear any pending show timeout
              if (showTimeout) {
                clearTimeout(showTimeout);
                showTimeout = null;
              }

              // Set hide timeout
              hideTimeout = setTimeout(() => {
                submenu.style.display = 'none';
                link.setAttribute('aria-expanded', 'false');
                // Clean up scrolling if enabled
                disableSubmenuScrolling(submenu);
                hideTimeout = null;
              }, HIDE_DELAY);
            }
          });

          if (isMobile() && isNestedSubmenu) {
            positionNestedSubmenu(submenu, link);
          }

          function toggleMenu() {
            const isExpanded = link.getAttribute('aria-expanded') === 'true';
            if (isExpanded) {
              slideUp(submenu, SLIDE_DELAY, () => {
                submenu.style.display = 'none';
                link.setAttribute('aria-expanded', 'false');
                link.classList.remove('highlighted')
                disableSubmenuScrolling(submenu);
              });
            } else {
              slideDown(submenu, SLIDE_DELAY, () => {
                submenu.style.display = 'block';
                link.classList.add('highlighted')
                link.setAttribute('aria-expanded', 'true');
              });
            }
          }

          // Mobile/Touch: toggle on click
          link.addEventListener('click', function(e) {
            if (isMobile()) {
              e.preventDefault();
              toggleMenu();
            }
          });

          // Keyboard navigation
          link.addEventListener('keydown', function(e) {
            if (e.key === 'Enter' || e.key === ' ') {
              e.preventDefault();
              toggleMenu();
            } else if (e.key === 'Escape') {
              submenu.style.display = 'none';
              link.setAttribute('aria-expanded', 'false');
              disableSubmenuScrolling(submenu);
              link.focus();
            }
          });
        }
      }
    });

    // Helper function to close all open dropdown menus
    closeAllDropdowns = function() {
      menuItems.forEach(item => {
        const submenu = item.querySelector('ul');
        const link = item.querySelector('a.has-submenu');
        if (submenu && link) {
          disableSubmenuScrolling(submenu);
          submenu.style.display = 'none';
          submenu.style.marginLeft = 0;
          link.setAttribute('aria-expanded', 'false');
          link.classList.remove('highlighted');
        }
      });
    };

    // Close all dropdown menus when clicking a link (navigation to new page or anchor)
    const allLinks = mainMenu.querySelectorAll('a');
    allLinks.forEach(link => {
      link.addEventListener('click', function() {
        // Close dropdowns when navigating (unless it's a has-submenu link in mobile mode)
        if (!link.classList.contains('has-submenu') || !isMobile()) {
          if (closeAllDropdowns) {
            closeAllDropdowns();
          }
        }
      });
    });
  }

  // Initialize dropdown menu behavior
  initDropdownMenu();

  // Close all open menus when browser back button is pressed
  window.addEventListener('popstate', function() {
    if (closeAllDropdowns) {
      closeAllDropdowns();
    }
  });
}

document.addEventListener('DOMContentLoaded', () => {
  const configElem = document.getElementById('doxygen-config');
  if (configElem) {
    const config = JSON.parse(configElem.textContent);
    initMenu(config.relPath, config.generateTreeView);
    if (config.searchEngine) {
      if (!config.serverBasedSearch) {
        if (!config.disableIndex && config.dynamicMenus && !config.fullSidebar) {
          if (typeof init_search === 'function') init_search();
        }
      } else {
        if (document.querySelector('.searchresults') && typeof searchBox !== 'undefined') {
          searchBox.DOMSearchField().focus();
        }
      }
    }
  }
});

/* @license-end */
