import mongoose from 'mongoose';

const UsuariosSchema = new mongoose.Schema({
  id: { type: Number, unique: true },
  username: { type: String, required: true, unique: true },
  password: { type: String, required: true },
  email: { type: String },
  address: {
    city: { type: String },
    street: { type: String },
    number: { type: Number },
    zipcode: { type: String },
  },
  name: {
    firstname: { type: String },
    lastname: { type: String },
  },
  phone: { type: String },
  carrito: [{ type: mongoose.Schema.Types.ObjectId, ref: 'productos' }],
});

// UsuariosSchema.pre('save', async function (next) {
//     if (this.isModified('password')) {
//       this.password = await bcrypt.hash(this.password, 10); // Hash de la contraseña
//     }
//     next();
// });

const Usuarios = mongoose.model('usuarios', UsuariosSchema);
export default Usuarios;
