# Imagen base con Apache y PHP
FROM php:7.4-apache

# Copia los archivos PHP al directorio de trabajo del contenedor
COPY index.php /var/www/html/
COPY alumnos.php /var/www/html/

# Habilita el módulo de Apache para PHP
RUN docker-php-ext-install mysqli
