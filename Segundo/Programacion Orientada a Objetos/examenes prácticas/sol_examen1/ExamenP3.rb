require_relative 'Damage'
require_relative 'Weapon'
require_relative 'ShieldBooster'
require_relative 'WeaponType'
require_relative 'SuppliesPackage'
require_relative 'SpaceStation'
module Deepspace
class Examen
	def self.principal
		#weap es un vector de WeaponType con 4 elementos
		weap=Array.new
		weap << WeaponType::PLASMA
		weap << WeaponType::LASER
		weap << WeaponType::PLASMA
		weap << WeaponType::MISSILE
		
		
		#damage es un objeto Damage que hace perder los elementos indicados en weap y 			#shields
		damage=Damage.newSpecificWeapons(weap,4)
		
		#muestra el objeto en la consola
		puts damage
		
		
		w1= Weapon.new("misil",WeaponType::MISSILE,2)
		w2=Weapon.new("laser",WeaponType::LASER,1)
		weapons_adjust =Array.new
		weapons_adjust << w1
		weapons_adjust << w2
		
		s1=ShieldBooster.new("Escudo_estacion",0.3,4)
		sh=Array.new
		sh << s1
		
		damage_ajustado = damage.adjust(weapons_adjust,sh)
		puts damage_ajustado
		
	end
end
	Examen.principal
end

