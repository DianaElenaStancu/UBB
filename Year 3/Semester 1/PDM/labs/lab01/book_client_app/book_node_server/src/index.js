const Koa = require('koa');
const app = new Koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({ server });
const Router = require('koa-router');
const cors = require('koa-cors');
const bodyparser = require('koa-bodyparser');

app.use(bodyparser());
app.use(cors());
app.use(async (ctx, next) => {
    const start = new Date();
    await next();
    const ms = new Date() - start;
    console.log(`${ctx.method} ${ctx.url} ${ctx.response.status} - ${ms}ms`);
});

app.use(async (ctx, next) => {
    await new Promise(resolve => setTimeout(resolve, 2000));
    await next();
});

app.use(async (ctx, next) => {
    try {
        await next();
    } catch (err) {
        ctx.response.body = { issue: [{ error: err.message || 'Unexpected error' }] };
        ctx.response.status = 500;
    }
});

class Book {
    constructor({ id, name, pageCount, dateAdded, alreadyRead}) {
        this.id = id;
        this.name = name;
        this.pageCount = pageCount;
        this.dateAdded = dateAdded;
        this.alreadyRead = alreadyRead;
    }
}

const books = [];
for (let i = 0; i < 3; i++) {
    books.push(new Book({ id: `${i}`, name: `book ${i}`, pageCount: `${i * 10 }`, dateAdded: new Date(Date.now() - i * 24 * 60 * 60 * 1000), alreadyRead: true}));
    // console.log(books);
    console.log(books[0]);
}
let lastUpdated = books[books.length - 1].dateAdded;
let lastId = books[books.length - 1].id;
const pageSize = 10;

const broadcast = data =>
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });

const router = new Router();

router.get('/book', ctx => {
    ctx.response.body = books;
    ctx.response.status = 200;
});

router.get('/book/:id', async (ctx) => {
    const bookId = ctx.request.params.id;
    const book = books.find(book => bookId === book.id);
    if (book) {
        ctx.response.body = book;
        ctx.response.status = 200; // ok
    } else {
        ctx.response.body = { message: `book with id ${bookId} not found` };
        ctx.response.status = 404; // NOT FOUND (if you know the resource was deleted, then return 410 GONE)
    }
});

const createItem = async (ctx) => {
    const book = ctx.request.body;
    if (!book.name && !book.pageCount && book.alreadyRead !== null) { // validation
        ctx.response.body = { message: 'Parameters are missing' };
        ctx.response.status = 400; //  BAD REQUEST
        return;
    }
    book.id = `${parseInt(lastId) + 1}`;
    lastId = book.id;
    books.push(book);
    ctx.response.body = book;
    ctx.response.status = 201; // CREATED
    broadcast({ event: 'created', payload: { book } });
};

router.post('/book', async (ctx) => {
     await createItem(ctx);
});

router.put('/book/:id', async (ctx) => {
    const id = ctx.params.id;
    const book = ctx.request.body;
    const bookId = book.id;
    if (bookId && id !== book.id) {
        ctx.response.body = { message: `Param id and body id should be the same` };
        ctx.response.status = 400; // BAD REQUEST
        return;
    }
    if (!bookId) {
        await createItem(ctx);
        return;
    }
    const index = books.findIndex(book => book.id === id);
    if (index === -1) {
        ctx.response.body = { issue: [{ error: `book with id ${id} not found` }] };
        ctx.response.status = 400; // BAD REQUEST
        return;
    }
    // const itemVersion = parseInt(ctx.request.get('ETag')) || book.alreadyRead;
    // if (itemVersion < books[index].alreadyRead) {
    //     ctx.response.body = { issue: [{ error: `Version conflict` }] };
    //     ctx.response.status = 409; // CONFLICT
    //     return;
    // }
    books[index] = book;
    lastUpdated = new Date();
    console.log(book);
    ctx.response.body = book;
    ctx.response.status = 200; // OK
    broadcast({ event: 'updated', payload: { book } });
});

router.del('/book/:id', ctx => {
    const id = ctx.params.id;
    const index = books.findIndex(book => id === book.id);
    if (index !== -1) {
        const book = books[index];
        books.splice(index, 1);
        lastUpdated = new Date();
        broadcast({ event: 'deleted', payload: { book } });
    }
    ctx.response.status = 204; // no content
});

// setInterval(() => {
//     lastUpdated = new Date();
//     lastId = `${parseInt(lastId) + 1}`;
//     const book = new Book({ id: `${lastId}`, name: `book ${lastId}`, pageCount: `${lastId * 10 }`, dateAdded: new Date(Date.now() - lastId * 24 * 60 * 60 * 1000), alreadyRead: lastId % 2 !== 0 })
//     books.push(book);
//     console.log(`New book: ${book.name}`);
//     broadcast({ event: 'created', payload: { book } });
// }, 5000);

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(3333);
