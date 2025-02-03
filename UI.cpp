#include "UI.h"

AUI::AUI()
{
    font.loadFromFile("sprites/nes.otf");

    // Configuracion de textos
    pointsText.setFont(font);
    pointsText.setCharacterSize(24);
    pointsText.setScale(0.15f, 0.15f);
    pointsText.setPosition(10, 1);
    pointsText.setFillColor(sf::Color(203, 232, 247));
    updatePoints(points);

    ragdollText.setFont(font);
    ragdollText.setCharacterSize(24);
    ragdollText.setScale(0.15f, 0.15f);
    ragdollText.setPosition(63, 1);
    ragdollText.setFillColor(sf::Color(203, 232, 247));
    updateRagdolls(ragdolls);

    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setScale(0.15f, 0.15f);
    levelText.setPosition(122, 1);
    levelText.setFillColor(sf::Color(203, 232, 247));
    updateLevel(level);
}

void AUI::updatePoints(int newPoints)
{
    points = newPoints;
    pointsText.setString("Points: " + std::to_string(points));
}

void AUI::updateRagdolls(int newRagdolls)
{
    ragdolls = newRagdolls;
    ragdollText.setString("Ragdolls: " + std::to_string(ragdolls));
}

void AUI::updateLevel(int newLevel)
{
    level = newLevel;
    levelText.setString("Level: " + std::to_string(level));
}

void AUI::render(sf::RenderWindow& window)
{
    window.draw(pointsText);
    window.draw(ragdollText);
    window.draw(levelText);
}