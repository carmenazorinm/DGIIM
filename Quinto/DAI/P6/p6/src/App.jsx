import { useState } from "react";
import useSWR from "swr";
import './App.css'

function BuyProduct({ product }) {
  return <>

    <div className="hero bg-base-200 min-h-screen">
      <div className="hero-content flex-col lg:flex-row">
        <img
          src={product.image}
          className="max-w-sm rounded-lg shadow-2xl" />
        <div>
          <h1 className="text-5xl font-bold">{product.title}</h1>
          <p className="py-6">
            {product.description}
             </p>
          <button className="btn btn-primary">Pagar</button>
        </div>
      </div>
    </div>
  </>
}


function App() {

  const [selectedProduct, setSelectedProduct] = useState();

  const { data, error, isLoading } = useSWR("products", () =>
    fetch("https://fakestoreapi.com/products")
      .then((res) => res.json()))

  console.log(data);

  if (isLoading) {
    return <>Loading...</>
  }

  if (selectedProduct) {
    return <BuyProduct product={selectedProduct} />
  }
  return (
    <div className='flex flex-row gap-3'>
      {data?.map(product => (
        <div key={product.id} className="card bg-base-100 w-96 shadow-xl">
          <figure>
            <img
              src={product.image}
              alt={product.title} />
          </figure>
          <div className="card-body">
            <h2 className="card-title">
              {product.title}
              <div className="badge badge-secondary">{product.price}</div>
            </h2>
            <p>{product.description}</p>
            <div className="card-actions justify-end">
              <div className="badge badge-outline">{product.category}</div>
            </div>
            <div>
              <button onClick={() => setSelectedProduct(product)} className="btn btn-xs sm:btn-sm md:btn-md lg:btn-lg">Buy now</button>
            </div>
          </div>
        </div>
      ))}
    </div>
  )
}

export default App
