#include "Traders.hpp"

#include "GameManager.hpp"
#include "DisplayableObject.hpp"
#include "HabitableObject.hpp"
#include "SFGManager.hpp"

#include "GameHelpers.hpp"
#include "Misc.h"
#include "Speed.hpp"
#include "MathHelpers.h"
#include "VectorHelpers.hpp"

Trader::Trader(DisplayableObject* a_pStartLocation)
:	DisplayableObject(DisplayableObject::TRADER, a_pStartLocation)
,	m_pCurrentDestination(NULL)
,	m_tLeftMainUpdate(1)
,	m_PercentTravelledThisLevel(0)
,	m_LastSqrdDist(9999999)
,	m_pCurrentDownwardTarget(NULL)
,	m_Money(0)
,	m_TotalCargoSpace(10000.f)
,	m_UsedCargoSpace(0.f)
{
	m_ImageName = "../media/ship.png";
	m_BGImageName = "../media/ship_bg.png";
	//
	mRelPosition = sf::Vector2f(0.5f, 0.5f);
	
	m_Name = GetRandomTraderName();

	std::string& name = m_Name;
	for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
	{
		m_CargoHold.insert( std::pair<Resource::ResourceType, float>(Resource::ResourceType(resInd), 0.f) );
		m_CargoQ.insert( std::pair<Resource::ResourceType, float>(Resource::ResourceType(resInd), 0.f) );
	}
}

void Trader::JumpToLocationMaintainHeading(DisplayableObject* a_pNewLocation, sf::Vector2f a_Coords)
{
	//this should only happen if the ship is trying to move outside the Spur
	if(!m_pParentObject)
	{
		m_pCurrentDestination = NULL;
		m_MoveDir = sf::Vector2f();
	}

	mRelPosition = a_Coords;
	m_pParentObject = a_pNewLocation;
	//
	GameManager::ShipChangeLevel(this);
}

void Trader::JumpToLocation(DisplayableObject* a_pNewLocation, sf::Vector2f a_Coords)
{
	//this should only happen if the ship is trying to move outside the Spur
	if(!m_pParentObject)
	{
		m_pCurrentDestination = NULL;
	}

	mRelPosition = a_Coords;
	m_pParentObject = a_pNewLocation;
	m_pCurrentDownwardTarget = NULL;
	m_MoveDir = sf::Vector2f();
	//
	GameManager::ShipChangeLevel(this);
}

void Trader::Update(TimeRate a_CurTimeRate, float a_DeltaT)
{
	if(!a_CurTimeRate)
		return;
	
	if(m_pCurrentDestination)
	{
		//check if we have a heading
		if(SquaredLength(m_MoveDir))
		{
			float realTimeToCross = GetRealtimeToCross(a_CurTimeRate, m_pParentObject->GetDisplayableType());
			bool arrived = false;
			float sqrdDistCovered = SquaredLength(m_MoveDir * (a_DeltaT / realTimeToCross));
			float sqrdDistToTarget = 0;
			if(m_pCurrentDownwardTarget && m_pCurrentDownwardTarget->GetParentDisplayableObject() == m_pParentObject)
			{
				sqrdDistToTarget = SquaredDistance(m_pCurrentDownwardTarget->GetRelPosition(), mRelPosition);
				if(sqrdDistToTarget <= sqrdDistCovered)
				{
					//std::cout << "moving down a level" << std::endl;
					arrived = true;
				}
			}
			else if(m_pCurrentDestination == m_pParentObject)
			{
				sqrdDistToTarget = SquaredDistance(m_TargetCoords, mRelPosition);
				if(sqrdDistToTarget <= sqrdDistCovered)
				{
					//std::cout << "inside destination" << std::endl;
					arrived = true;
				}
			}

			//if(realTimeToCross < 120)
			mRelPosition += m_MoveDir * (a_DeltaT / realTimeToCross);
			//m_PercentTravelledThisLevel += a_DeltaT / GetRealtimeToCross(a_CurTimeRate, m_pParentObject->GetDisplayableType());
			
			//check if we've reached our target
			if(arrived)
			{
				if(m_pCurrentDestination == m_pParentObject)
				{
					//we've arrived
					ArrivedAtDestination();
				}
				else if(m_pCurrentDownwardTarget)
				{
					//we're moving towards something on the same level as us
					//arrived, move to the outer edges of the screen
					sf::Vector2f arrivePos = -m_MoveDir;
					if(arrivePos.x < 0)
						arrivePos.x = 0;
					if(arrivePos.y < 0)
						arrivePos.y = 0;
					if(arrivePos.x > 0)
						arrivePos.x = 1;
					if(arrivePos.y > 0)
						arrivePos.y = 1;
					//
					JumpToLocation(m_pCurrentDownwardTarget, arrivePos);
					//m_pSFGImage->Show(false);
					GameManager::ShipChangeLevel(this);
						
					//std::cout << "Moved down a level" << std::endl;
				}
			}
			//check if we've moved offscreen
			if(mRelPosition.x > 1 || mRelPosition.y > 1 || mRelPosition.x < 0 || mRelPosition.y < 0)
			{
				JumpToLocationMaintainHeading(m_pParentObject->GetParentDisplayableObject(), m_pParentObject->GetRelPosition());

				GameManager::ShipChangeLevel(this);
				//std::cout << "Moved up a level" << std::endl;
			}

			if(GameManager::GetCurrentlyViewedObject() == m_pParentObject)
			{
				sf::Vector2f windowDims = SFGManager::GetSingleton().GetWindowDimensions();
				sf::Vector2f halfWindowDims = windowDims;
				//
				windowDims.x *= 5.f/6.f;
				windowDims.x -= SPRITE_DIM;
				windowDims.y *= 5.f/6.f;
				windowDims.y -= SPRITE_DIM;
				halfWindowDims.x /= 2.f;
				halfWindowDims.y /= 2.f;

				sf::Vector2f newPos = windowDims;
				newPos.x *= mRelPosition.x;
				newPos.y *= mRelPosition.y;
				//
				m_pSFGImage->SetPosition(newPos);
			}

			//check if we've reached our destination
			//todo
		}
		else
		{
			//calculate a heading and rerun this update
			CalculateHeading();
			Update(a_CurTimeRate, a_DeltaT);
		}
	}
	else
	{
		//todo: time delayed loading stuff onto the ship?
		//

		//for now, choose a random planet then head there
		//std::cout << "Destination chosen" << std::endl;
		m_pCurrentDestination = (HabitableObject*)GameManager::GetRandomTraderDestination(this);
		/*std::vector<Planet*> viableChoices = GameManager::GetValidDestinations();
		int numChoices = viableChoices.size();
		if(numChoices)
		{
			int destIndex = iRand(0, numChoices);
			m_pCurrentDestination = (HabitableObject*)viableChoices[destIndex];
		}*/
	}
}

void Trader::CalculateHeading()
{
	if(m_pCurrentDestination == m_pParentObject)
	{
		//if we're inside the destination, just head to the center for now
		m_TargetCoords = sf::Vector2f(0.5f, 0.5f);
		if(mRelPosition == m_TargetCoords)
		{
			ArrivedAtDestination();
		}
		else
		{
			m_MoveDir = NormaliseCopy(m_TargetCoords - mRelPosition);
		}
	}
	else if(m_pCurrentDestination->GetParentDisplayableObject() == m_pParentObject)
	{
		//if we're at the same level as the destination
		if(m_pCurrentDestination->GetRelPosition() == mRelPosition)
		{
			ArrivedAtDestination();
		}
		else
		{
			//if we're on the same level as the target, head straight there
			m_pCurrentDownwardTarget = m_pCurrentDestination;
			m_MoveDir = NormaliseCopy(m_pCurrentDestination->GetRelPosition() - mRelPosition);
		}
	}
	else
	{
		//otherwise, work out which direction to head off in
		DisplayableObject* pCurMyLoc = m_pParentObject;
		DisplayableObject* pCurDownwardTarget = m_pCurrentDestination;
		while(pCurMyLoc->GetParentDisplayableObject() != pCurDownwardTarget->GetParentDisplayableObject())
		{
			//first, loop through all ancestors of the destination node to see if any match our current node's parent
			DisplayableObject* pDestinationCheck = pCurDownwardTarget;
			//break when we reach a child of the root node OR the parent of pDestinationCheck matches pCurMyLoc.parent
			while(pDestinationCheck->GetParentDisplayableObject()->GetDisplayableType() != DisplayableObject::ORIONSPUR && pDestinationCheck->GetParentDisplayableObject() != pCurMyLoc->GetParentDisplayableObject())
			{
				//move up one level
				pDestinationCheck = pDestinationCheck->GetParentDisplayableObject();
			}
			
			//at this point, one of two things are true
			//either destinationChecker is a child of the root node, or it's parent is the one we're after
		
			//if the latter case, we can do this and forgo the next loop to calculate our heading
			if(pDestinationCheck->GetParentDisplayableObject() == pCurMyLoc->GetParentDisplayableObject())
			{
				pCurDownwardTarget = pDestinationCheck;
			}
			else
			{
				//otherwise, move up a level and try again next loop
				pCurMyLoc = pCurMyLoc->GetParentDisplayableObject();
			}
		}

		m_pCurrentDownwardTarget = pCurDownwardTarget;
		m_TargetCoords = pCurDownwardTarget->GetRelPosition();
		m_MoveDir = NormaliseCopy(pCurDownwardTarget->GetRelPosition() - pCurMyLoc->GetRelPosition());
	}
}

void Trader::GenerateContents()
{
	//
}

void Trader::ArrivedAtDestination()
{
	//sell goods if the current colony is buying them for more than the average price
	for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
	{
		Resource::ResourceType curResType = Resource::ResourceType(resInd);
		float averagePrice = GameManager::GetAveragePrice(curResType);
		float localPrice = m_pCurrentDestination->GetResPrice(curResType);
		float freeCargoSpace = m_TotalCargoSpace - m_UsedCargoSpace;

		if(m_CargoHold[curResType] > 0 && localPrice > averagePrice)
		{
			//sell these goods
			m_pCurrentDestination->AddResources(curResType, m_CargoQ[curResType], m_CargoHold[curResType]);
			m_Money += m_pCurrentDestination->GetResPrice(curResType) * m_CargoHold[curResType];
			m_CargoHold[curResType] = 0;
		}
	}

	//buy goods if they're below the average price
	for(int resInd = 0; resInd < Resource::MAXVAL; ++resInd)
	{
		Resource::ResourceType curResType = Resource::ResourceType(resInd);
		float averagePrice = GameManager::GetAveragePrice(curResType);
		float localPrice = m_pCurrentDestination->GetResPrice(curResType);
		float freeCargoSpace = m_TotalCargoSpace - m_UsedCargoSpace;

		//only keep buying as long as we have room
		if(freeCargoSpace <= 0)
			break;

		if(localPrice < averagePrice)
		{
			//buy some of these goods
			float targetPurchase = min(m_TotalCargoSpace / 5.f, freeCargoSpace);
			float availableRes = m_pCurrentDestination->GetStoredResNum(curResType);
			if(targetPurchase >= availableRes)
			{
				if(IsCriticalResource(curResType))
				{
					//don't buy it
					continue;
				}
				else if(IsImportantResource(curResType))
				{
					//only buy half of it
					targetPurchase = availableRes / 2.f;
				}
				else
				{
					//buy all of it anyway
					targetPurchase = availableRes;
				}
				
				m_pCurrentDestination->RemoveResources(curResType, targetPurchase);
				m_Money -= m_pCurrentDestination->GetResPrice(curResType) * targetPurchase;
				m_CargoQ[curResType] = AverageWeight(m_CargoQ[curResType], m_CargoHold[curResType], m_pCurrentDestination->GetStoredResQ(curResType), targetPurchase);
				m_CargoHold[curResType] += targetPurchase;
			}
		}
	}
	
	//std::cout << "Arrived" << std::endl;
	m_pCurrentDestination = NULL;
	m_MoveDir = sf::Vector2f();
}

std::string Trader::GetName()
{
	return m_Name;
}
