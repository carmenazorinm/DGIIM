document.addEventListener('DOMContentLoaded', () => {
  console.log('Iniciando fetch ...');
  const ele_stars = document.getElementsByClassName('stars'); // Todos los elementos de la clase 'stars'

  for (const ele of ele_stars) {
    const ide = ele.dataset._id; // _id está en los atributos del dataset

    // Fetch para obtener la calificación
    fetch(`/api/ratings/${ide}`)
      .then(response => response.json())
      .then(data => {
        const rating = Math.round(data.rating.rate || 0); // Redondear rating
        let html_nuevo_con_las_estrellas = '';

        // Crear las estrellas
        for (let i = 1; i <= 5; i++) {
          if (i <= rating) {
            html_nuevo_con_las_estrellas += '<span class="fa fa-star checked" data-star="' + i + '" data-_id="' + ide + '"></span>'; // Estrella dorada
          } else {
            html_nuevo_con_las_estrellas += '<span class="fa fa-star" data-star="' + i + '" data-_id="' + ide + '"></span>'; // Estrella vacía
          }
        }

        ele.innerHTML = html_nuevo_con_las_estrellas;

        // Añadir los manejadores de eventos
        addEventListenersToStars(ele);
      })
      .catch(error => {
        console.error(`Error al obtener el rating para ${ide}:`, error);
        ele.innerHTML = 'Error al cargar estrellas';
      });
  }
});

// Función para añadir eventos de clic a las estrellas
function addEventListenersToStars(ele) {
  for (const ele_hijo of ele.children) {
    if (ele_hijo.tagName === 'SPAN' && ele_hijo.classList.contains('fa-star')) {
      ele_hijo.addEventListener('click', Vota);
    }
  }
}

// Función para manejar el evento de click en una estrella
function Vota(evt) {
  const ide = evt.target.dataset._id;  // ID del producto
  const pun = parseInt(evt.target.dataset.star, 10); // Valor de la estrella seleccionada

  const esEstrella = evt.target.classList.contains('fa-star') && evt.target.dataset.star;

  if (esEstrella) {
    console.log(`Se ha clicado en la estrella con valor ${evt.target.dataset.star}`);
    // Registra la votación en el logger
    fetch('/api/logger', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ action: `Se clicó en la estrella de ${ide} con valor ${pun}`, timestamp: new Date() })
    });

    // Enviar la calificación al API (PUT en lugar de POST)
    fetch(`/api/ratings/${ide}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ rating: pun })
    })
      .then(response => response.json())
      .then(data => {
        // Actualizar las estrellas y número de votos con la respuesta del servidor
        const ele = evt.target.parentElement; // Contenedor de las estrellas
        renderStars(ele, data.rating.rate, data.rating.count);
      })
      .catch(error => {
        console.error(`Error al enviar la calificación para ${ide}:`, error);
      });
  } else {
    console.log('El clic no fue en una estrella.');
  }
}

// Función para renderizar las estrellas en la UI
function renderStars(ele, rating, count) {
  rating = Math.round(rating || 0); // Redondear rating
  let html_nuevo_con_las_estrellas = '';

  for (let i = 1; i <= 5; i++) {
    if (i <= rating) {
      html_nuevo_con_las_estrellas += `<span class="fa fa-star checked" data-star="${i}" data-_id="${ele.dataset._id}"></span>`;
    } else {
      html_nuevo_con_las_estrellas += `<span class="fa fa-star" data-star="${i}" data-_id="${ele.dataset._id}"></span>`;
    }
  }

  html_nuevo_con_las_estrellas += `<span> (${count || 0} votos)</span>`;
  ele.innerHTML = html_nuevo_con_las_estrellas;

  // Añadir manejadores de eventos a las estrellas nuevamente
  addEventListenersToStars(ele);
}
