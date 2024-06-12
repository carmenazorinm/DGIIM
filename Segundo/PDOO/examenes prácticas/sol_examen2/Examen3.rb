require_relative 'SpaceStation'
require_relative 'SuppliesPackage'
require_relative 'Damage'
require_relative 'Hangar'
require_relative 'Weapon'
require_relative 'WeaponType'
require_relative 'ShieldBooster'
module Test
class Examen3
	
	def principal
		supplies=Deepspace::SuppliesPackage.new(2,5,3)
		spaceStation=Deepspace::SpaceStation.new("carmen",supplies)
		
		puts spaceStation 
		puts "(2.a)"
		
		hangar=Deepspace::Hangar.new(3)
		spaceStation.receiveHangar(hangar)
		
		puts spaceStation
		puts "(2.b)"
		
		weapon=Deepspace::Weapon.new("Espada",Deepspace::WeaponType::LASER,1)
		spaceStation.receiveWeapon(weapon)
		
		puts spaceStation
		puts "(2.c)"
		
		3.times do
			spaceStation.receiveWeapon(weapon)
		end	
		
		puts spaceStation
		puts "(2.d)"
		
		spaceStation.mountWeapon(0)
		spaceStation.mountWeapon(1)
		
		puts spaceStation
		puts "(2.e)"
		
		shieldBooster=Deepspace::ShieldBooster.new("Escudo",1.5,2)
		spaceStation.receiveShieldBooster(shieldBooster)
		
		puts spaceStation
		puts "(2.f)"
		
		2.times do
			spaceStation.receiveShieldBooster(shieldBooster)
		end
		
		puts spaceStation
		puts "(2.g)"
		
		spaceStation.mountShieldBooster(1)
		
		puts spaceStation
		puts "(2.h)"
		
		#------------- Pregunta 3------------------
		weap = Array.new
		weap << Deepspace::WeaponType::PLASMA
		weap << Deepspace::WeaponType::LASER
		weap << Deepspace::WeaponType::MISSILE
		damage2=Deepspace::Damage.newSpecificWeapons(weap,3)
		
		puts damage2
		puts "(3.b)"
		
		weapons_adjust=Array.new
		weapons_adjust << Deepspace::Weapon.new("a",Deepspace::WeaponType::LASER,1)
		weapons_adjust << Deepspace::Weapon.new("b",Deepspace::WeaponType::MISSILE,1)
		weapons_adjust << Deepspace::Weapon.new("c",Deepspace::WeaponType::LASER,1)
		
		shields_adjust=Array.new
		shields_adjust << Deepspace::ShieldBooster.new("d",1.5,2)
		shields_adjust << Deepspace::ShieldBooster.new("e",1.5,2)
		
		damage3 = damage2.adjust(weapons_adjust,shields_adjust)
		
		puts damage3
		puts "(3.c)"
	end
end
examen = Examen3.new
examen.principal
end


