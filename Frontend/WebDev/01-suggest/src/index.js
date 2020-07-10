const labels = document.getElementsByClassName('input__label');
const inputs = document.getElementsByClassName('input__text');
const suggestions = document.getElementsByClassName('suggestions');
const deleters = document.getElementsByClassName('input__deleter');
const swapButton = document.getElementsByClassName('swap__button')[0];

const SUGGEST_INPUTS_AMOUNT = 2;
const SUGGEST_LIST_MAX_SIZE = 5;

let suggestFocusIndex;
let inputFocusIndex;

let suggestList = [];
let airports = [];
fetch('static/airports.json')
  .then(response => response.json())
  .then(json => (airports = json.airports));

const SUGGESTION_HOVER_COLOR = '#ffeba0';
const INPUT_BOX_SHADOW_FOCUS = 'inset 0 0 0 2px rgba(0, 0, 0, 0.5)';
const defaultBoxShadow = [];

const inputEvent = new Event('input');

swapButton.onclick = () => {
  [inputs[0].value, inputs[1].value] = [inputs[1].value, inputs[0].value];

  for (let j = 0; j < SUGGEST_INPUTS_AMOUNT; j++) {
    inputs[j].dispatchEvent(inputEvent);
    clear(suggestions[j]);
  }
};

for (let i = 0; i < inputs.length; i++) {
  inputs[i].onfocus = () => {
    const labelStyle = labels[i].style;

    if (defaultBoxShadow[i] === undefined) {
      defaultBoxShadow[i] = labelStyle.boxShadow;
    }

    labelStyle.boxShadow = INPUT_BOX_SHADOW_FOCUS;

    for (let j = 0; j < SUGGEST_INPUTS_AMOUNT; j++) {
      if (i !== j) {
        clear(suggestions[j]);
      }
    }
  };

  inputs[i].onblur = () => {
    labels[i].style.boxShadow = defaultBoxShadow[i];
  };
}

for (let i = 0; i < SUGGEST_INPUTS_AMOUNT; i++) {
  deleters[i].onclick = () => {
    inputs[i].value = '';

    for (let j = 0; j < SUGGEST_INPUTS_AMOUNT; j++) {
      inputs[j].dispatchEvent(inputEvent);
    }
  };

  inputs[i].oninput = () => {
    deleters[i].style.display = inputs[i].value !== '' ? 'block' : 'none';
  };

  ['keyup', 'focus'].forEach(changeEvent => {
    inputs[i].addEventListener(changeEvent, function() {
      inputFocusIndex = i;
      clear(suggestions[i]);

      const curInput = inputs[i].value.toLowerCase();
      if (curInput.length === 0) {
        return;
      }

      airports
        .filter(airport => {
          return compareInput(airport, curInput) !== undefined;
        })
        .slice(0, SUGGEST_LIST_MAX_SIZE)
        .forEach(hint => {
          const button = document.createElement('button');
          button.className = 'suggest suggestions__suggest';
          formatSuggest(hint, curInput, button);

          suggestions[i].append(button);
          suggestList.push([
            button,
            onKeyDownHandler(button),
            onClickHandler(button),
            onHoverHandler(suggestions[i].childElementCount - 1),
            onMouseOutHandler()
          ]);
        });

      suggestList.forEach(
        ([button, keyDownHandler, clickHandler, hoverHandler, mouseOutHandler]) => {
          button.addEventListener('keydown', keyDownHandler);
          button.addEventListener('click', clickHandler);
          button.addEventListener('focus', hoverHandler);
          button.addEventListener('mouseover', hoverHandler);
          button.addEventListener('mouseout', mouseOutHandler);
        }
      );
    });
  });

  inputs[i].onkeydown = event => {
    if (event.key === 'ArrowDown' && suggestList[0] !== undefined) {
      suggestions[inputFocusIndex].firstElementChild.focus();
    }
  };
}

function onKeyDownHandler(button) {
  return function(event) {
    if (event.key === 'Enter') {
      onClickHandler(button);
    } else if (event.key === 'ArrowDown') {
      suggestions[inputFocusIndex].children[
        ((suggestFocusIndex || 0) + 1) % suggestList.length
      ].focus();
    } else if (event.key === 'ArrowUp') {
      suggestions[inputFocusIndex].children[
        (suggestList.length + (suggestFocusIndex || 0) - 1) % suggestList.length
      ].focus();
    } else {
      suggestFocusIndex = undefined;
      inputs[inputFocusIndex].focus();
    }
  };
}

function onClickHandler(button) {
  return function() {
    inputs[inputFocusIndex].value = button.firstElementChild.innerHTML;
    clear(suggestions[inputFocusIndex]);
  };
}

function onHoverHandler(buttonIndex) {
  return function() {
    if (suggestFocusIndex !== undefined) {
      suggestions[inputFocusIndex].children[suggestFocusIndex].style.backgroundColor = '';
    }

    suggestFocusIndex = buttonIndex;
    suggestions[inputFocusIndex].children[
      suggestFocusIndex
    ].style.backgroundColor = SUGGESTION_HOVER_COLOR;
  };
}

function onMouseOutHandler() {
  return function() {
    suggestions[inputFocusIndex].children[suggestFocusIndex].style.backgroundColor = '';
    suggestFocusIndex = undefined;
  };
}

function compareInput(airport, curInput) {
  if (airport.city.toLowerCase().startsWith(curInput)) {
    return airport.city;
  } else if (airport.name.toLowerCase().startsWith(curInput)) {
    return airport.name;
  } else if (airport.IATA.toLowerCase().startsWith(curInput)) {
    return airport.IATA;
  }

  return undefined;
}

function formatSuggest(suggestedItem, curInput, parentButton) {
  const primalInput = compareInput(suggestedItem, curInput);

  const primalChildDiv = document.createElement('div');
  primalChildDiv.className = 'suggest__main';
  primalChildDiv.innerHTML = primalInput;
  parentButton.append(primalChildDiv);

  const secondaryChildDiv = document.createElement('span');
  secondaryChildDiv.className = `suggest__secondary`;
  secondaryChildDiv.innerHTML = Array.from(
    new Set(
      Object.values(suggestedItem).filter(property => {
        return property !== primalInput;
      })
    )
  )
    .reverse()
    .join(' · ');
  parentButton.append(secondaryChildDiv);
}

function clear(curSuggestions) {
  suggestList.forEach(([button, keyDownHandler, clickHandler, hoverHandler, mouseOutHandler]) => {
    button.removeEventListener('keydown', keyDownHandler);
    button.removeEventListener('click', clickHandler);
    button.removeEventListener('focus', hoverHandler);
    button.removeEventListener('mouseover', hoverHandler);
    button.removeEventListener('mouseout', mouseOutHandler);
  });

  suggestList = [];
  curSuggestions.innerHTML = '';
}
