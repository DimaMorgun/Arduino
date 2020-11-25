const parsedTrCollection = [];

(function getTableData() {
    let trCollection = this.window.document.getElementsByTagName('tr');

    for (let element of trCollection) {
        if (!element.classList.contains('not-filtered')) {
            parsedTrCollection.push(element);
        }
    }
})();

(function addCollapsForRows() {
    for (let element of parsedTrCollection) {
        element.prepend(createCollapsItem());
    }
})();

function createCollapsItem() {
    let styleClass = 'collaps-cell';

    let td = document.createElement('td');
    td.classList.add(styleClass);
    td.addEventListener('click', handleCollapsClick)

    return td;
}

function handleCollapsClick(event) {
    let collapsedRowStyleClass = 'collapsed-row';
    let row = event.path[1];

    if (row.classList.contains(collapsedRowStyleClass)) {
        row.classList.remove(collapsedRowStyleClass);
    }
    else {
        row.classList.add(collapsedRowStyleClass);
    }


    console.log(row);
}