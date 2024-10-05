
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Clases de gestión de VAOs y VBOs (implementación). 
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Declaración de las clases
// **   + DescrVBOAtribs -descriptor de VBO de una tabla de atributos.
// **   + DescrVBOInds - descriptor de VBO de índices 
// ***  + DescrVAO - descriptor de VAOs
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "vaos-vbos.h"
    
constexpr GLsizei stride = 0 ;
constexpr void *  offset = 0 ;
constexpr GLint   first  = 0 ;

// ------------------------------------------------------------------------------------------------------
// devuelve el tamaño en bytes de un valor a partir de entero asociado con el tipo del valor en OpenGL

constexpr inline GLsizeiptr size_in_bytes( const GLenum type )
{
   switch( type )
   {
      case GL_FLOAT          : return sizeof( float );          break ;
      case GL_DOUBLE         : return sizeof( double );         break ;
      case GL_UNSIGNED_BYTE  : return sizeof( unsigned char );  break ;
      case GL_UNSIGNED_SHORT : return sizeof( unsigned short ); break ;
      case GL_UNSIGNED_INT   : return sizeof( unsigned int );   break ;
      default                : assert( false ); return 0 ;      break ;
   }
}

// ----------------------------------------------------------------------------
// 
constexpr inline void comprobar_tipo_atrib( const GLenum type )
{
   assert( type == GL_FLOAT  || 
           type == GL_DOUBLE );
}

// ----------------------------------------------------------------------------
// 
constexpr inline void check_indices_type( const GLenum type )
{
   assert( type == GL_UNSIGNED_BYTE  || 
           type == GL_UNSIGNED_SHORT || 
           type == GL_UNSIGNED_INT   );
}

// ------------------------------------------------------------------------------------------------------
// comprueba que el modo es válido para las llamadas glDrawArrays y glDrawElements

constexpr void check_mode( const GLenum mode )
{
   assert( mode == GL_TRIANGLES  || mode == GL_LINES || mode == GL_POINTS || 
           mode == GL_LINE_STRIP || mode == GL_LINE_LOOP  );  
}

// ******************************************************************************************************
// Clase DescrVBOAtribs
// ------------------------------------------------------------------------------------------------------

DescrVBOAtribs::DescrVBOAtribs( const unsigned p_index, const GLenum p_type, const unsigned p_size, 
                                const unsigned long p_count, const void *p_data )
{
   // copiar valores de entrada y comprobar que son correctos
   index    = p_index ; // índice de atributo (<num_attrs)
   type     = p_type ; // tipo de valores (GL_FLOAT o GL_DOUBLE)
   size     = p_size ; // número de valores por tupla (2,3,4)
   count    = p_count ; // número de tuplas en la tabla (>0)
   data     = p_data ; // datos originales en la CPU
   tot_size = size*count*size_in_bytes( type ); // tamaño completo
   // Además en copiarDatos() se crea el atributo own_data que son datos propiedad de este objeto
   // También podríamos tener la variable buffer que indica el nombre del VBO para OpenGL. Inicialmente 0, una
   // vez alojado en la GPU, pasará a ser >0.
   copiarDatos();
   comprobar() ; 
}  

// ------------------------------------------------------------------------------------------------------
 
DescrVBOAtribs::DescrVBOAtribs( const unsigned p_index, const std::vector<glm::vec3> & src_vec )
{
   index    = p_index ;
   type     = GL_FLOAT ;
   size     = 3 ;
   count    = src_vec.size();
   data     = src_vec.data();
   tot_size = size*count*size_in_bytes( type );
   
   copiarDatos() ;
   comprobar();
}

// ----------------------------------------------------------------------------

DescrVBOAtribs::DescrVBOAtribs( const unsigned p_index, const std::vector<glm::vec2> & src_vec )
{
   index    = p_index ;
   type     = GL_FLOAT ;
   size     = 2 ;
   count    = src_vec.size();
   data     = src_vec.data();
   tot_size = size*count*size_in_bytes( type );
   
   copiarDatos();
   comprobar();
}

// --------------------------------------------------------------------------------------

void DescrVBOAtribs::copiarDatos()
{
   assert( data != nullptr );     // 'data' debe apuntar a los datos originales
   assert( 0 < tot_size );        // 'tot_size' debe tener el tamaño total de los datos
   assert( own_data == nullptr ); // impide copiar los datos dos veces 

   // esto es para crear una copia de los datos en memoria -> 
   own_data = new unsigned char [tot_size] ; // reservar memoria
   assert( own_data != nullptr );            // comprobar que se ha podido reservar la memoria
   std::memcpy( own_data, data, tot_size );  // copiar bytes
   data = own_data ;                         // apuntar a los datos propios -> modifica el atributo data?
}

// --------------------------------------------------------------------------------------

void DescrVBOAtribs::comprobar() const 
{
   comprobar_tipo_atrib( type );

   assert( data != nullptr );
   assert( 0 < count );
   assert( own_data == nullptr || own_data == data );
   assert( 1 <= size && size <= 4 ); 
   assert( type == GL_FLOAT || type == GL_DOUBLE );
   assert( tot_size == size*count*size_in_bytes( type ));
}

// ------------------------------------------------------------------------------------------------------

void DescrVBOAtribs::crearVBO() 
{
   // comprobar precondiciones
   CError();
   assert( buffer == 0 ); // al principio el VBO no esta alojado en la GPU y su indice es 0
   comprobar();

   /* APUNTES CLASE:
   OpenGL siempre tiene un VBO activo (el 0, no usable), se debe cambiar para operar con otros VBOs.
   Para poder crear y poblar VBOs dentro del VAO activo, se pueden usar funciones gl...
   */

   // COMPLETAR: práctica 1: crear el VBO de atributos en la GPU
   //
   // añadir el código para crear el VBO (transferir datos y registrar metadatos), se 
   // deben de dar estos pasos:
   //
   // 1. generar un nuevo identificador o nombre de VBO 
      // glGenBuffers crea uno o varios VBOs, se obtiene el identificador nuevo de cada uno. 
      // 1 indica que se crea un VBO y &buffer indica que se guarda el identificador en la variable buffer
   glGenBuffers(1,&buffer);
   // 2. fija este buffer como buffer 'activo' actualmente en el 'target' GL_ARRAY_BUFFER
      // glBindBuffer activa un buffer ya creado, usando su identificador.
   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   // 3. transferir los datos desde la memoria de la aplicación al VBO en GPU
      // glBufferData reserva memoria para el VBO activo y transfiere un bloque de bytes desde la memoria hacia GPU
   glBufferData(GL_ARRAY_BUFFER, tot_size, data, GL_STATIC_DRAW);
   // 4. registrar, para este índice de atributo, la localización y el formato de la tabla en el buffer 
      // especifica como se interpretan los datos en el VBO. size y type es de los componentes; GL_FALSE para que no 
      // se normalicen los valores
   glVertexAttribPointer( index, size, type, GL_FALSE, stride, offset  );   
   // 5. desactivar el bufferbuffer
      // desactiva VBO para no interferur con posteriores operaciones con otros VBOs en el mismo VAO pero con distinto indice
   glBindBuffer(GL_ARRAY_BUFFER,0);
   // 6. habilitar el uso de esta tabla de atributos
      // activa la matriz genérica de atributos de vértices especificada por el índice y utiliza el objeto de 
      // matriz de vértices enlazado para la operación. -> Habilita la tabla
   glEnableVertexAttribArray(index);


   // comprobar que no ha habido error durante la creación del VBO
   CError();
}
// ------------------------------------------------------------------------------------------------------

DescrVBOAtribs::~DescrVBOAtribs()
{
   delete [] (unsigned char *) own_data ;
   own_data = nullptr ; // probablemente innecesario
   
   if ( buffer != 0 )
   {
      CError();
      glDeleteBuffers( 1, &buffer );
      CError();
      buffer = 0 ; // probablemente innecesario
   }

}

// ******************************************************************************************************
// Clase DescrVBOInds
//
// descriptor de VBOs de índices
// ------------------------------------------------------------------------------------------------------

 
DescrVBOInds::DescrVBOInds( const GLenum p_type, const GLsizei p_count, const void * p_indices )
{
   // buffer = nombre del buffer en la GPU (0 by default)
   type     = p_type ; // tipo de datos de cada indice
   count    = p_count ; // numero de indices en la tabla
   indices  = p_indices ; // datos originales o su copia
   tot_size = count*size_in_bytes( type ) ; // tamaño de los datos en bytes (=count*sizeof(c-type))
   
   copyIndices();
   comprobar();
}
// ------------------------------------------------------------------------------------------------------

DescrVBOInds::DescrVBOInds( const std::vector<unsigned> & src_vec )
{
   type     = GL_UNSIGNED_INT ;
   count    = src_vec.size() ;
   indices  = src_vec.data() ;
   tot_size = count*size_in_bytes( type ) ;
   
   copyIndices();
   comprobar();
}
// ------------------------------------------------------------------------------------------------------

DescrVBOInds::DescrVBOInds( const std::vector<glm::uvec3> & src_vec )
{
   type     = GL_UNSIGNED_INT ;
   count    = 3*src_vec.size() ;
   indices  = src_vec.data() ;
   tot_size = count*size_in_bytes( type ) ;

   copyIndices();
   comprobar();
}
// ------------------------------------------------------------------------------------------------------

void DescrVBOInds::copyIndices()
{
   assert( indices != nullptr );     // 'indices' debe apuntar a los indices originales
   assert( 0 < tot_size );           // 'tot_size' debe tener el tamaño total de los datos
   assert( own_indices == nullptr ); // impide copiar los datos dos veces 

   own_indices = new unsigned char [tot_size] ;    // reservar memoria
   assert( own_indices != nullptr );               // comprobar que se ha podido reservar
   std::memcpy( own_indices, indices, tot_size );  // copiar bytes
   indices = own_indices ;                         // apuntar a los índices propios
}

// ------------------------------------------------------------------------------------------------------

void DescrVBOInds::comprobar() const 
{
   assert( indices != nullptr ); 
   check_indices_type( type );
   assert( 0 < count );
   assert( type == GL_UNSIGNED_BYTE || type == GL_UNSIGNED_SHORT || type == GL_UNSIGNED_INT  );
   assert( tot_size == count*size_in_bytes( type ));
}
// ------------------------------------------------------------------------------------------------------

void DescrVBOInds::crearVBO( )
{
   // comprobar precondiciones:
   CError(); // comprobar y limpiar errores previos de OpenGL
   assert( buffer == 0 );                 // impedir que se llame más de una vez para este objeto
   comprobar();                           // comprobar que este objeto está en un estado correcto

   // COMPLETAR: práctica 1: crear el VBO de índices en la GPU
   //
   // Añadir el código para crear el VBO en la GPU y transferir los datos, se deben 
   // de dar estos pasos:
   //
   // 1. crear un nuevo nombre o identificador de VBO 
   glGenBuffers(1,&buffer);
   // 2. activar ('bind') el buffer en el 'target' GL_ELEMENT_ARRAY_BUFFER
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
   // 3. transferir los datos desde la memoria de la aplicación al VBO en GPU
      // GL_STATIC_DRAW -> El contenido del almacén de datos se modificará una vez y se utilizará muchas veces como 
      // fuente para los comandos de dibujo GL.
      // GL_DYNAMIC_DRAW -> El contenido del almacén de datos se modificará repetidamente y se utilizará muchas veces 
      // como fuente para los comandos de dibujo GL. 
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, tot_size, indices, GL_STATIC_DRAW);

      
   // comprueba que no ha habido error al crear el VBO 
   CError();
}
// ---------------------------------------------------------------------------------------------

DescrVBOInds::~DescrVBOInds()
{
   delete [] (unsigned char *) own_indices ;
   own_indices = nullptr ; // probablemente innecesario

   if ( buffer != 0 )
   {
      CError();
      glDeleteBuffers( 1, &buffer );
      CError();
      buffer = 0 ; // probablemente innecesario
   }
}

// ******************************************************************************************************
// Clase DescrVAO
// ------------------------------------------------------------------------------------------------------



DescrVAO::DescrVAO( const unsigned p_num_atribs, DescrVBOAtribs * p_dvbo_posiciones ) 
{
   // comprobar precondiciones 
   assert( 0 < p_num_atribs );
   assert( p_dvbo_posiciones != nullptr ); // no se permite puntero nulo, debe apuntar a algún objeto
   assert( p_dvbo_posiciones->leerIndex() == 0 ); // solo se permite el atributo de posiciones (con índice 0)
   p_dvbo_posiciones->comprobar() ; // comprobar que el vbo está en un estado correcto.
   
   // registrar el número de atributos -> el numero es 4,pero es mejor usar la constante numero_atributos_cauce de cauce.h
   num_atribs = p_num_atribs ;

   // crear el vector con punteros a los descriptores de VBOs (todos a null)
   dvbo_atributo.resize( num_atribs, nullptr ); 

   // crear el vector con los flags de habilitado/deshabilitado (todos a 'true', por defecto están habilitados)
   atrib_habilitado.resize( num_atribs, true );

   // registrar el número de vértices en la tabla de posiciones
   count = p_dvbo_posiciones->leerCount() ;

   // clonar el descriptor de VBO de posiciones y apuntarlo desde este objeto
   dvbo_atributo[0] = p_dvbo_posiciones ;  
}
// ------------------------------------------------------------------------------------------------------

// Comprueba que el estado del VAO es correcto justo antes de añadir una tabla de atributos con índice 'index' 
// (aborta si no)
//
void DescrVAO::check( const unsigned index )
{
   assert( dvbo_atributo[0] != nullptr ); // el VAO ya debe tener el VBO de posiciones.
   assert( 0 < index );  // no permite el índice 0, son las posiciones y se dan al construir el VAO
   assert( index < num_atribs ); // no permite índices fuera de rango
   assert( dvbo_atributo[index] == nullptr ); // no permite añadir un atributo dos veces 
   assert( array == 0 ); // no permite añadir atributos si el VAO ya esá alojado en la GPU
}
// ----------------------------------------------------------------------------

// agregar al VAO un descripto de VBO
void DescrVAO::agregar( DescrVBOAtribs * p_dvbo_atributo )
{
   // comprobar precondiciones
   assert( p_dvbo_atributo != nullptr );
   const unsigned index = p_dvbo_atributo->leerIndex();
   check( index );
   p_dvbo_atributo->comprobar();
   assert( count == p_dvbo_atributo->leerCount() ); // debe tener el mismo núm de items que el VBO posiciones

   // registrar el descriptor de VBO en la tabla de descriptores de VBOs de atributos
   dvbo_atributo[index] = p_dvbo_atributo ;
}
// ----------------------------------------------------------------------------

void DescrVAO::agregar( DescrVBOInds * p_dvbo_indices )
{
   // comprobar precondiciones:
   assert( p_dvbo_indices != nullptr ); // no permite añadir atributos si el VAO ya esá alojado en la GPU
   p_dvbo_indices->comprobar();

   // registrar el número de índices (3 por tupla) y el tipo
   idxs_count = p_dvbo_indices->leerCount() ;
   idxs_type  = p_dvbo_indices->leerType() ;

   // crear el descriptor VBO y referenciarlo desde este objeto 
   dvbo_indices = p_dvbo_indices ;
}
// ------------------------------------------------------------------------------------------------------

// Crea el VAO en la GPU (solo se puede llamar una vez), deja el VAO activado como VAO actual.
// Crea y activa el VBO de posiciones y todos los VBOs de atributos que se hayan añadido.
// Si se ha añadido una tabla de índices, crea y activa el VBO de índices.
//
void DescrVAO::crearVAO()
{
   CError();
   assert( array == 0 ); // asegurarnos que únicamente se invoca una vez para este descriptor

   // COMPLETAR: práctica 1: crear el VAO y enviar datos de VBOs
   //
   // Escribir el código que crea el VAO en la GPU y registra (asocia) 
   // los VBOs en este VAO. Se deben dar estos pasos:
   //
   // 1. Crear el nombre de VAO y activarlo como VAO actual (hacer 'bind')
   glGenVertexArrays(1, &array);
   glBindVertexArray(array);
   // 2. Para cada VBO de atributos adjunto al VAO (puntero en 'dvbo_atributo' no nulo):
   //       Crear el VBO de atributos en la GPU (usar 'crearVBO')  
   dvbo_atributo[0]->crearVBO(); // se utiliza -> porque dvbo_atributo[0] es un puntero
   for (unsigned i = 1; i < num_atribs; i++){
      if (dvbo_atributo.at(i) != nullptr)
         dvbo_atributo.at(i)->crearVBO();
   }
   // 3. Si hay índices (puntero dvbo_indices no nulo) entonces, 
   //       Crear el VBO de índices (usar método 'crearVBO')
   if (dvbo_indices != nullptr) {
      dvbo_indices->crearVBO();
   } 
   // 4. Para cada VBO de atributos adjunto al VAO (puntero en 'dvbo_atributo' no nulo):
   //       Si la tabla está deshabilitada en el vector 'atrib_habilitado':
   //           Deshabilitarla en la GPU con 'glDisableVertexAttribArray')
   // el profe usa dvbo_atributo[i] que no hace comprobaciones y es mas rapido
   for (unsigned i = 0; i < num_atribs; i++) {
      if(dvbo_atributo.at(i) != nullptr && !atrib_habilitado.at(i)) {
         glDisableVertexAttribArray(dvbo_atributo[i]->buffer);
      }
   }


   CError();
}
// ------------------------------------------------------------------------------------------------------

// Habilita o deshabilita una tabla de atributos en este VAO 
//
// @param index (unsigned) índice del atributo a habilitar o deshabilitar (no puede ser 0)
// @param habilitar (boolean) 'true' para habilitar y 'false' para deshabilitar
//
void DescrVAO::habilitarAtrib( const unsigned index, const bool habilitar )
{
   // comprobar precondiciones
   assert( 0 < index ); // el atributo 0 siempre está habilitado, no puede deshabilitarse
   assert( index < num_atribs ); // al índice debe estar en su rango
   assert( dvbo_atributo[index] != nullptr ); // no tiene sentido usarlo para un atributo para el cual no hay tabla

   // registrar el nuevo valor del flag
   atrib_habilitado[index] = habilitar ;
   
   // si el VAO ya se ha enviado a la GPU, actualizar estado del VAO en OpenGL
   if ( array != 0 )
   {
      CError();
      glBindVertexArray( array );
      
      if ( habilitar ) 
         glEnableVertexAttribArray( index );
      else 
         glDisableVertexAttribArray( index );

      glBindVertexArray( 0 );
      CError();
   }

}
// ------------------------------------------------------------------------------------------------------

// Visualiza los vértices de este VAO, usando un modo determinado
//
// @param mode (GLenum) modo de visualización (GL_TRIANGLES, GL_LINES, GL_POINTS,  GL_LINE_STRIP o GL_LINE_LOOP)
//
void DescrVAO::draw( const GLenum mode )
{

   CError();
   assert( dvbo_atributo[0] != nullptr ); // asegurarnos que hay una tabla de coordenadas de posición.
   check_mode( mode );                // comprobar que el modo es el correcto.
   
   // COMPLETAR: práctica 1: visualizar el VAO
   //
   // se debe de escribir código que da estos pasos:
   //
   // 1. Comprobar si el array se ha creado o no (antes de crearse, 'array' vale 0, después es >0). 
   //    Si el array no se ha creado todavía:
   //     - crear el VAO en la GPU (método 'crearVAO'), el VAO queda activado 
   //    Si el array ya se ha creado:
   //     - activar el VAO (con 'glBindVertexArray')
   if (array == 0) {
      crearVAO();
   } else {
      glBindVertexArray(array);
   }

   CError(); // el profe lo pone
   // 2. Comprobar si la secuencia es indexada o no lo es (si no es indexada 'dvbo_indices' es nulo)
   //    Si la secuencia es indexada
   //     - visualizar con 'glDrawElements'
   //    Si la secuencia no es indexada 
   //     - visualizar con 'glDrawArrays'
   if (dvbo_indices != nullptr) {
      glDrawElements(mode, idxs_count, idxs_type, offset );
   } else {
      // mode es tipo de primitiva; 
      // first es el índice del primer vertice
      // count es el número de vértices
      glDrawArrays(mode, first, count);
   }

   CError();
   // 3. Desactivar el VAO (activar el VAO 0 con 'glBindVertexArray')
   glBindVertexArray(0);


   CError();
}
// ------------------------------------------------------------------------------------------------------

// Libera toda la memoria ocupada por el VAO y los VBOs en la memoria de 
// la aplicación y en la GPU. Invalida los identificadores de VBOs y el del VAO
//
DescrVAO::~DescrVAO()
{
   for( unsigned i = 1 ; i < num_atribs ; i++ )
   {  
      delete dvbo_atributo[i] ;
      dvbo_atributo[i] = nullptr ; 
   }
   
   delete dvbo_indices ;
   dvbo_indices = nullptr ; 
   
   if ( array != 0 )
   {
      CError();
      glDeleteVertexArrays( 1, &array );
      CError();
      array = 0 ; // probablemente innecesario
   }
}
// ------------------------------------------------------------------------------------------------------





