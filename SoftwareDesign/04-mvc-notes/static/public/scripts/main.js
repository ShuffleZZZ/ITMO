// Modal

const modal = document.querySelector(".modal");
const html = document.querySelector("html");

const showModal = () => {
  modal.classList.add("is-active");
  html.classList.add("is-clipped");
};

const hideModal = () => {
  modal.classList.remove("is-active");
  html.classList.remove("is-clipped");
};

document.querySelector("a.show-modal").addEventListener("click", function(e) {
  e.preventDefault();
  showModal();
});

modal.querySelector(".modal .delete").addEventListener("click", function(e) {
  e.preventDefault();
  hideModal();
});

// Form submission

const form = document.querySelector("#note-form");
const url = form.getAttribute("action");
const method = form.getAttribute("method");

const prependList = html => {
  const listsList = document.querySelector(".lists-list");
  const div = document.createElement("div");
  div.innerHTML = html;
  for (let i = 0; i < listsList.children.length; i++) {
    console.log(listsList.children[i].firstChild);
    if (listsList.children[i].firstChild.textContent === div.firstChild.firstChild.textContent) {
      listsList.removeChild(listsList.children[i]);
    }
  }
  console.log(listsList.children);
  listsList.insertBefore(div.firstChild, listsList.firstChild);
  console.log(listsList.children);
};

const onSuccess = html => {
  hideModal();
  form.reset();

  prependList(html);
};

form.addEventListener("submit", e => {
  e.preventDefault();

  fetch(url, {
    method,
    body: new FormData(form)
  })
    .then(response => response.text())
    .then(text => onSuccess(text))
    .catch(error => console.error(error));
});
