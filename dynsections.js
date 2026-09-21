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

// Simple tooltip implementation
document.addEventListener('DOMContentLoaded', function() {
  // Create hidden tooltip container
  const tooltip = document.createElement('div');
  tooltip.id = 'powerTip';
  tooltip.style.position = 'absolute';
  tooltip.style.display = 'none';
  tooltip.style.zIndex = '9999';
  document.body.appendChild(tooltip);

  let currentElement = null;
  let hideTimeout = null;

  function showTooltip(element, content) {
    clearTimeout(hideTimeout);
    currentElement = element;

    // Materialize tooltip so we can compute its size
    tooltip.innerHTML = content;
    tooltip.style.display = 'block';

    // Compute the position of the tooltip with respect to the source
    const sourceRect = element.getBoundingClientRect();
    const tooltipRect = tooltip.getBoundingClientRect();

    // Ideal position
    let left = sourceRect.left + (sourceRect.width - tooltipRect.width) / 2;
    let top = sourceRect.bottom;

    // Check if tooltip goes off screen
    const margin = 10;
    if (left < margin) left = margin;
    if (left + tooltipRect.width + margin > window.innerWidth) {
      left = window.innerWidth - tooltipRect.width - margin;
    }

    // If tooltip would go below viewport, show above element instead
    if (top + tooltipRect.height > window.innerHeight) {
      top = sourceRect.top - tooltipRect.height;
    }

    // Set computed position
    tooltip.style.left = left + window.scrollX + 'px';
    tooltip.style.top = top + window.scrollY + 'px';
  }

  function hideTooltip() {
    hideTimeout = setTimeout(() => {
      tooltip.style.display = 'none';
      currentElement = null;
    }, 100);
  }

  // Add hover listeners to code elements
  document.querySelectorAll('.code,.codeRef').forEach(sourceElement => {
    const href = sourceElement.getAttribute('href');
    if (!href) return;

    // Get tooltip content from data attribute or related sourceElement
    const targetId = 'a' + href.replace(/.*\//, '').replace(/[^a-z_A-Z0-9]/g, '_');
    const targetElement = document.getElementById(targetId);
    const targetContent = targetElement ? targetElement.innerHTML : null;
    if (targetContent) {
      sourceElement.addEventListener('mouseenter', () => showTooltip(sourceElement, targetContent));
      sourceElement.addEventListener('mouseleave', () => hideTooltip());
      sourceElement.addEventListener('focus', () => showTooltip(sourceElement, targetContent));
      sourceElement.addEventListener('blur', () => hideTooltip());
    }
  });

  // Allow mouse to enter tooltip without hiding it
  tooltip.addEventListener('mouseenter', () => clearTimeout(hideTimeout));
  tooltip.addEventListener('mouseleave', () => hideTooltip());
});
/* @license-end */
