import mongoose from 'mongoose';
//import bcrypt from 'bcrypt';

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
  admin: {
    type: Boolean,
    default: false, // Por defecto, los usuarios no son administradores
    required: false
  },
});

// UsuariosSchema.pre('save', async function (next) {
//   if (this.isModified('password')) {
//       const salt = await bcrypt.genSalt(10); // Generar un salt
//       this.password = await bcrypt.hash(this.password, salt); // Cifrar contraseña
//   }
//   next();
// });

// // Método para verificar contraseñas
// UsuariosSchema.methods.compararPassword = async function (password) {
//   return await bcrypt.compare(password, this.password);
// };

const Usuarios = mongoose.model('usuarios', UsuariosSchema);
export default Usuarios;
