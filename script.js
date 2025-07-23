class TrieNode {
  constructor() {
    this.children = {};
    this.isEnd = false;
  }
}

class Trie {
  constructor() {
    this.root = new TrieNode();
  }

  insert(word) {
    let node = this.root;
    for (let char of word.toLowerCase()) {
      if (!node.children[char]) {
        node.children[char] = new TrieNode();
      }
      node = node.children[char];
    }
    node.isEnd = true;
  }

  startsWith(prefix) {
    let node = this.root;
    for (let char of prefix.toLowerCase()) {
      if (!node.children[char]) return [];
      node = node.children[char];
    }
    return this._collect(node, prefix.toLowerCase());
  }

  _collect(node, prefix) {
    let results = [];
    if (node.isEnd) results.push(prefix);
    for (let char in node.children) {
      results = results.concat(this._collect(node.children[char], prefix + char));
    }
    return results;
  }
}

const trie = new Trie();
const events = [];

function addEvent() {
  const title = document.getElementById("title").value.trim();
  const description = document.getElementById("description").value.trim();
  const date = document.getElementById("date").value;
  const time = document.getElementById("time").value;

  if (!title || !description || !date || !time) {
    alert("Please fill all fields.");
    return;
  }

  const event = { title, description, date, time };
  events.push(event);
  trie.insert(title);

  displayEvents();
  clearFields();
}

function displayEvents() {
  const list = document.getElementById("eventList");
  list.innerHTML = "";
  events.forEach(event => {
    const div = document.createElement("div");
    div.className = "event";
    div.innerHTML = `<strong>${event.title}</strong><br>${event.description}<br><em>${event.date} at ${event.time}</em>`;
    list.appendChild(div);
  });
}

function clearFields() {
  document.getElementById("title").value = "";
  document.getElementById("description").value = "";
  document.getElementById("date").value = "";
  document.getElementById("time").value = "";
}

function handleSearch() {
  const prefix = document.getElementById("searchInput").value.trim();
  const matches = trie.startsWith(prefix);
  const resultsDiv = document.getElementById("searchResults");
  resultsDiv.innerHTML = "<h3>Matched Titles:</h3>" + (matches.length ?
    matches.map(m => `<p>${m}</p>`).join("") :
    "<p>No matches found</p>");
}
