## @file calculateexampleinfantryfire.py
# do example calculations of what damage will be dealt towards the enemy

ATTACKER_ORG = 100
ATTACKER_SUPPLY_LVL = 100

DEFENDER_ORG = 100
DEFENDER_SUPPLY_LVL = 100

PLAIN_DEFENCE_PUNISHMENT = 1.0

TERRAIN_COEFFICIENT = PLAIN_DEFENCE_PUNISHMENT #plain - best to attack

baseIIAttack = 60 #base Infantry-to-infantry attack

#base attack - best conditions for both sides (but no terrain bonus)

#to start an attack unit needs org >= 25
MINIMUM_ATTACKER_ORG = 25

ATTACKER_ORG_IMPORTANCE = 0.05
DEFENDER_ORG_IMPORTANCE = 0.3
ATTACKER_SUPPLY_LVL_IMPORTANCE = 0.4
DEFENDER_SUPPLY_LVL_IMPORTANCE = 0.25

damage = baseIIAttack*TERRAIN_COEFFICIENT \
 - (100-ATTACKER_ORG)*ATTACKER_ORG_IMPORTANCE \
 + (100-DEFENDER_ORG)*DEFENDER_ORG_IMPORTANCE \
 - (100-ATTACKER_SUPPLY_LVL)*ATTACKER_SUPPLY_LVL_IMPORTANCE \
 + (100-DEFENDER_SUPPLY_LVL)*DEFENDER_SUPPLY_LVL_IMPORTANCE

if ATTACKER_ORG <= MINIMUM_ATTACKER_ORG:
    damage = 0.0


print(f'Damage={damage}')