#pragma once
#include "../../Headers.h"

FVertexSimple cube_vertices[] =
{
	// Front face (Z+)
	{ -0.5f, -0.5f,  0.5f }, // Bottom-left (red)
	{ -0.5f,  0.5f,  0.5f }, // Top-left (yellow)
	{  0.5f, -0.5f,  0.5f }, // Bottom-right (green)
	{ -0.5f,  0.5f,  0.5f }, // Top-left (yellow)
	{  0.5f,  0.5f,  0.5f }, // Top-right (blue)
	{  0.5f, -0.5f,  0.5f }, // Bottom-right (green)

	// Back face (Z-)
	{ -0.5f, -0.5f, -0.5f }, // Bottom-left (cyan)
	{  0.5f, -0.5f, -0.5f }, // Bottom-right (magenta)
	{ -0.5f,  0.5f, -0.5f }, // Top-left (blue)
	{ -0.5f,  0.5f, -0.5f }, // Top-left (blue)
	{  0.5f, -0.5f, -0.5f }, // Bottom-right (magenta)
	{  0.5f,  0.5f, -0.5f }, // Top-right (yellow)

	// Left face (X-)
	{ -0.5f, -0.5f, -0.5f }, // Bottom-left (purple)
	{ -0.5f,  0.5f, -0.5f }, // Top-left (blue)
	{ -0.5f, -0.5f,  0.5f }, // Bottom-right (green)
	{ -0.5f,  0.5f, -0.5f }, // Top-left (blue)
	{ -0.5f,  0.5f,  0.5f }, // Top-right (yellow)
	{ -0.5f, -0.5f,  0.5f }, // Bottom-right (green)

	// Right face (X+)
	{  0.5f, -0.5f, -0.5f }, // Bottom-left (orange)
	{  0.5f, -0.5f,  0.5f }, // Bottom-right (gray)
	{  0.5f,  0.5f, -0.5f }, // Top-left (purple)
	{  0.5f,  0.5f, -0.5f }, // Top-left (purple)
	{  0.5f, -0.5f,  0.5f }, // Bottom-right (gray)
	{  0.5f,  0.5f,  0.5f }, // Top-right (dark blue)

	// Top face (Y+)
	{ -0.5f,  0.5f, -0.5f }, // Bottom-left (light green)
	{ -0.5f,  0.5f,  0.5f }, // Top-left (cyan)
	{  0.5f,  0.5f, -0.5f }, // Bottom-right (white)
	{ -0.5f,  0.5f,  0.5f }, // Top-left (cyan)
	{  0.5f,  0.5f,  0.5f }, // Top-right (brown)
	{  0.5f,  0.5f, -0.5f }, // Bottom-right (white)

	// Bottom face (Y-)
	{ -0.5f, -0.5f, -0.5f }, // Bottom-left (brown)
	{ -0.5f, -0.5f,  0.5f }, // Top-left (red)
	{  0.5f, -0.5f, -0.5f }, // Bottom-right (purple)
	{ -0.5f, -0.5f,  0.5f }, // Top-left (red)
	{  0.5f, -0.5f,  0.5f }, // Top-right (green)
	{  0.5f, -0.5f, -0.5f }, // Bottom-right (purple)
};