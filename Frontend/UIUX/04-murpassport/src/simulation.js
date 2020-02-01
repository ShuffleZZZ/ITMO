let isSimulationEnabled = false;

window.enableSimulation = function () {
  if (isSimulationEnabled) {
    console.log('simulation has already enabled');

    return;
  }

  isSimulationEnabled = true;

  const styleNode = getStyleNode();

  let cursor = window.document.createElement('div');

  cursor.className='mouse';
  window.document.body.appendChild(cursor);

  let needAnimate = true;
  window.document.addEventListener('mouseenter', function(){needAnimate = true});
  window.document.addEventListener('mouseleave', function(){needAnimate = false});

  window.document.addEventListener('mousemove', move);

  const cursorInterval = window.setInterval(animate, 100);
  const styleInterval = window.setInterval(addStyle, 100);

  addStyle();

  let lastX = -100;
  let lastY = -100;

  function move(event) {
    const { clientX, clientY } = event;

    lastX = clientX;
    lastY = clientY;

    randomizeCoords();
  }


  function animate() {
    randomizeCoords()
  }

  function randomizeCoords() {
    if(!needAnimate) {
      setPosition(-1000, -1000);

      return;
    }

    const maxOffset = 100;

    const y = parseInt(lastY);
    const x = parseInt(lastX);

    setPosition(getRandomArbitrary(x, maxOffset), getRandomArbitrary(y, maxOffset));
  }

  function getRandomArbitrary(start, offset) {
    return (Math.random() - 0.5) * offset + start;
  }

  function setPosition(x, y) {
    cursor.style.left = x + 'px';
    cursor.style.top = y + 'px';
  }

  function addStyle() {
    if(!window.document.head.contains(styleNode)) {
      window.document.head.appendChild(styleNode);
    }
  }

  window.disableSimulation = function () {
    if (!isSimulationEnabled) {
      console.log('please enable simulation');

      return;
    }

    window.clearInterval(cursorInterval);
    window.clearInterval(styleInterval);

    window.document.head.removeChild(styleNode);

    isSimulationEnabled = false;
  }
};


function getStyleNode() {
  const styleNode = window.document.createElement('style');

  styleNode.setAttribute('type', 'text/css');
  styleNode.innerHTML = `
    html, body, body *{
      cursor: none !important;
    }
    
    body *{
      filter: blur(6px);
    }

    .mouse {
      position: absolute;
      background-image: url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiA/PjwhRE9DVFlQRSBzdmcgIFBVQkxJQyAnLS8vVzNDLy9EVEQgU1ZHIDEuMC8vRU4nICAnaHR0cDovL3d3dy53My5vcmcvVFIvMjAwMS9SRUMtU1ZHLTIwMDEwOTA0L0RURC9zdmcxMC5kdGQnPjxzdmcgZW5hYmxlLWJhY2tncm91bmQ9Im5ldyAwIDAgMjQgMjQiIGlkPSJMYXllcl8xIiB2ZXJzaW9uPSIxLjAiIHZpZXdCb3g9IjAgMCAyNCAyNCIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayI+PHBhdGggZD0iTTcsMmwxMiwxMS4ybC01LjgsMC41bDMuMyw3LjNsLTIuMiwxbC0zLjItNy40TDcsMTguNVYyIi8+PC9zdmc+');
      z-index: 300000000;
      width: 20px;
      height: 20px;

      transform: translate(-25%, -5%);

      transition-property: top, left;
      filter: blur(0);
    }
    `;

  return styleNode;
}
